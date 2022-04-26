
def get_content():
    with open("interface.txt", "r") as interface:
        return interface.read()

def get_lines():
    with open("interface.txt", "r") as interface:
        return interface.readlines()
def extract_data(data):
    array = []
    current_object_pointer = -1
    for line in data:
        if line == '' or line == '\n' or not (line.find(':') != -1 or line.find('=') != -1):
            continue
        if line[-2] == ':':
            array.append({"Object": line.replace(':\n', '')})
            current_object_pointer += 1
        else:
            line = line.replace('\n', '')
            array[current_object_pointer].setdefault(line.split("=")[0], line.split("=")[1])

    return array


if __name__ == "__main__":
    print(extract_data(get_lines()))