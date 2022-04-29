import Interface
import pygame
import random
import math
import os
from os import path
import psutil
import sys
import time


def is_commander_running():
    for proc in psutil.process_iter():
        if "Gate Commander.exe" in str(proc.name):
            return True
    return False
def search_interface(way):
    tree = list(os.walk(way))
    for i in tree:
        if "Interface.txt" in i[2]:
            return i[0] + "\Interface.txt"
    return None

pygame.init()
img_dir = "Sprites"
#snd_dir = path.join(path.dirname(__file__), 'sounds')
#vid_dir = path.join(path.dirname(__file__), 'videos')


WIDTH = 1024
HEIGHT = 1024
FPS = 60

#Цвета
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)
PURPLE = (111, 50, 168)
SPRITEBG = (48, 12, 38)

#параметры рабочего окна
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("GATE VISUAL")
clock = pygame.time.Clock()

#создание фона
background_img = pygame.image.load(path.join(img_dir, 'bg.png')).convert()
background_rect = pygame.Rect(0, 0, WIDTH, HEIGHT)
background_rect.center = (WIDTH // 2, HEIGHT // 2)

#определение текстур для спрайтов
gate_img = pygame.image.load(path.join(img_dir, "gate1.png")).convert()
open_gate_img = pygame.image.load(path.join(img_dir, "gate2.png")).convert()
car_images = []
car_list = ['car1.png', 'car2.png', 'car3.png']
for img in car_list:
    car_images.append(pygame.image.load(path.join(img_dir, img)).convert())

def draw_text(surf, text, size, x, y, color):
    font_name = pygame.font.match_font('Avenir Regular')
    font_name = 'fonts/Metropolis-Bold.otf'
    font = pygame.font.Font(font_name, size)
    text_surface = font.render(text, True, color)
    text_rect = text_surface.get_rect()
    text_rect.topleft = (x, y)
    surf.blit(text_surface, text_rect)

class Gate(pygame.sprite.Sprite):
    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.sprite_height = int(WIDTH * .60)
        self.sprite_width = int(3623*self.sprite_height/4167)
        self.height = int(WIDTH * .60)
        self.width = int(3623*self.sprite_height/4167)
        self.health = 100
        self.shoot_delay = 300
        self.last_shot = pygame.time.get_ticks()
        self.lastpulse = pygame.time.get_ticks()
        self.image = pygame.transform.scale(gate_img, (self.width, self.height))
        self.image.set_colorkey(SPRITEBG)
        self.rect = self.image.get_rect()
        self.rect.centerx = WIDTH / 3
        self.rect.centery = HEIGHT / 3.5
        self.radius = int(self.rect.width / 4)
        self.opened = False
        self.is_changed = False

    def ESP(self):
        pygame.draw.circle(self.image, YELLOW, self.rect.center, self.radius, 2)
    def open(self):
        self.opened = True
        self.is_changed = True
    def close(self):
        self.opened = False
        self.is_changed = True
    def toggle(self):
        if self.opened:
            self.opened = False
        else:
            self.opened = True
        self.is_changed = True
    def is_open(self):
        if self.opened:
            return True
        return False
    def update(self):
        if self.is_changed:
            if self.opened == True:
                self.image = pygame.transform.scale(open_gate_img, (self.width, self.height))
                self.image.set_colorkey(SPRITEBG)
            else:
                self.image = pygame.transform.scale(gate_img, (self.width, self.height))
                self.image.set_colorkey(SPRITEBG)
        self.is_changed = False
        # убить, если он заходит за верхнюю часть экрана
        if self.rect.bottom < 0:
            self.kill()
class Car(pygame.sprite.Sprite):
    def __init__(self, direction):
        self.direction = direction
        pygame.sprite.Sprite.__init__(self)
        self.sprite_height = int(WIDTH * .30)
        self.sprite_width = int(640*self.sprite_height/1280)
        self.height = int(WIDTH * .30)
        self.width = int(640*self.sprite_height/1280)
        self.health = 100
        self.shoot_delay = 300
        self.last_shot = pygame.time.get_ticks()
        self.lastpulse = pygame.time.get_ticks()
        self.image_orig = random.choice(car_images)
        self.image = pygame.transform.scale(self.image_orig, (self.width, self.height))
        self.image.set_colorkey(SPRITEBG)
        self.rect = self.image.get_rect()
        if self.direction == "up":
            self.rect.centerx = WIDTH / 2.7
            self.rect.bottom = HEIGHT - 10
        elif self.direction == "down":
            self.rect.centerx = WIDTH / 1.4
            self.rect.bottom = 0
            self.image = pygame.transform.rotate(self.image, 180)
            self.speedy = 10
        self.radius = int(self.rect.width / 4)
        self.opened = False
        self.speedy = 0

    def get_direction(self):
        return self.direction
    def ESP(self):
        pygame.draw.circle(self.image, YELLOW, self.rect.center, self.radius, 2)
    def move_to_parking(self):
        if self.direction == 'up':
            self.speedy = -10
        else:
            self.speedy = 10
    def get_number(self):
        return self.number
    def update(self):
        # убить, если он заходит за верхнюю часть экрана
        #if self.direction == "up" and gate.is_open():
            #self.move_to_parking()
        if self.speedy != 0:
            self.rect.y += self.speedy
        if self.rect.bottom < 0 or self.rect.top > HEIGHT:
            self.kill()

#заполнение групп спрайтов
all_sprites = pygame.sprite.Group()
gate_sprite_group = pygame.sprite.Group()
car_sprite_group = pygame.sprite.Group()
gate = Gate()
gate_sprite_group.add(gate)
all_sprites.add(gate)

#Переменные цикла
total = None
free = None
running = True
FIRST_CHECK_RUNNING = True
WAITING_SCREEN = False
WAITING_INTERFACE_TABLE = False
interface_path = None
previous_data = None
exe_checking_last_time = time.time() - 3


while running:
    clock.tick(FPS)
    #Проверка запущен ли командер
    if FIRST_CHECK_RUNNING:
        if (time.time() - exe_checking_last_time) > 2:
            exe_checking_last_time = time.time()
            if not is_commander_running():
                WAITING_SCREEN = True
                total = None
                free = None
                gate.close()
                for obj in car_sprite_group:
                    car_sprite_group.remove(obj)
                    all_sprites.remove(obj)
            else:
                WAITING_SCREEN = False
                FIRST_CHECK_RUNNING = False

    if not interface_path:
        if "Interface.txt" not in os.listdir():
            interface_path = search_interface('.')
            if interface_path != None:
                print("Интерфейс найден: " + interface_path)
                previous_data = Interface.get_content(interface_path)
                WAITING_INTERFACE_TABLE = False
            else:
                print("Интерфейс не найден")
                if not WAITING_SCREEN:
                    WAITING_INTERFACE_TABLE = True
                time.sleep(1)
        else:
            interface_path = "Interface.txt"
            print("Интерфейс найден: " + interface_path)
            previous_data = Interface.get_content(interface_path)
            WAITING_INTERFACE_TABLE = False
    #Обработка событий
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                running = False
            if event.key == pygame.K_F1:
                car = Car("up")
                car_sprite_group.add(car)
                all_sprites.add(car)
            if event.key == pygame.K_F2:
                gate.toggle()
            if event.key == pygame.K_F3:
                car.move_to_parking()
            if event.key == pygame.K_F4:
                car = Car("down")
                car_sprite_group.add(car)
                all_sprites.add(car)
                car.move_to_parking()
    if interface_path:
        data = Interface.get_lines(interface_path)
        if data != previous_data:
            array = Interface.extract_data(data)
            if len(array) > 0:
                print("Получены указания: " + str(array))
            for dictionary in array:
                if dictionary.get('Object') == 'Global':
                    if dictionary.get('Event') == 'Clear':
                        gate.close()
                        total = None
                        free = None
                        for obj in car_sprite_group:
                            car_sprite_group.remove(obj)
                            all_sprites.remove(obj)

                if dictionary.get('Object') == 'Gate':
                    if dictionary.get('Opened') == 'True':
                        gate.open()
                    else:
                        gate.close()
                if dictionary.get('Object') == 'Parking':
                    total = int(dictionary.get('Total'))
                    free = int(dictionary.get('Free'))
                if dictionary.get('Object') == 'Car':
                    if dictionary.get('Event') == 'Create':
                        car = Car(dictionary.get('Direction'))
                        car_sprite_group.add(car)
                        all_sprites.add(car)
                    if dictionary.get('Event') == 'Forward':
                        for obj in car_sprite_group:
                            if obj.get_direction() == "up":
                                obj.move_to_parking()
                    if dictionary.get('Direction') == "down":
                        car.move_to_parking()
            previous_data = data
            Interface.clean_interface(interface_path)
    # Обновление
    all_sprites.update()
    screen.fill(BLACK)
    screen.blit(background_img, background_rect)
    all_sprites.draw(screen)
    draw_text(screen, 'Total: ' + str(total), int(WIDTH * .04), WIDTH * .02, HEIGHT * .10 - int(WIDTH * .07) / 2, WHITE)
    draw_text(screen, 'Free: ' + str(free), int(WIDTH * .04), WIDTH * .02, HEIGHT * .15 - int(WIDTH * .07) / 2,
              WHITE)
    gate_sprite_group.draw(screen)
    #Если коммандер не запущен
    if WAITING_SCREEN:
        screen.fill(BLACK)
        draw_text(screen, 'Waiting Gate Commander.exe', int(WIDTH * .05), WIDTH * .15,
                  HEIGHT * .5 - int(WIDTH * .05) / 2,
                  WHITE)
    if WAITING_INTERFACE_TABLE:
        screen.fill(BLACK)
        draw_text(screen, 'Waiting Interface.txt creating', int(WIDTH * .05), WIDTH * .15,
                  HEIGHT * .5 - int(WIDTH * .05) / 2,
                  WHITE)
    # После отрисовки всего, переворачиваем экран
    pygame.display.flip()