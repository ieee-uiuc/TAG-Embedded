import json as j
import hashlib as hl
import os
import shutil
import Queue
import requests
import random
import json
import hashlib
import string

'''
    Question 1: What is the word in the file named ___?
    Question 2: How many words does the file named ___ have?
    Question 3: How many files and directories are there all together including the initial dir?
    Question 4: How many files start with the letter _? (Files not dirs)
    Question 5: What is the word on the third to last line of the file named ___?
    Question 6: What is the size of the largest file? (In kilobytes)
    Question 7: How many directories have ___ many children?
    Question 8: What is the frequency of the word ___ in the files of the directory tree?
    Question 9: How many directories have no immediate file children?
    Question 10: What is the frequency of the word appearing the maximum number of times in files, as file names, and as directory names?
'''
GAME_NAME = "linux_game_space"
MAX_DIR_CHILDREN = 4
MAX_FILE_CHILDREN = 6
MAX_FILES = 1000
MAX_DIRS = 2000
MAX_WORDS = 500
WORD_SITE = "http://svnweb.freebsd.org/csrg/share/dict/words?view=co&content-type=text/plain" # Name of site to get words from


if os.getlogin() == "root":
    print("Don't run as root")

try:
    shutil.rmtree(GAME_NAME)
    print("Deleting old game")
except Exception as e:
    pass

# Create first dir in structure
print("Beginning create process")
os.mkdir(GAME_NAME)

directory_number = 0
file_number = 0
depth = 1
bfs_q = Queue.Queue(maxsize=0)
resp = requests.get(WORD_SITE) # Get words for use in game
words_list = map(lambda str: str.lower(), resp.content.splitlines()) #convert words to lowercase


# Generate game stats
question_one_file_name = random.choice(words_list)
question_one_file_number = random.randint(1, MAX_FILES - 1);
words_list.remove(question_one_file_name)
question_one_word_in_file = random.choice(words_list)
question_two_file_name = random.choice(words_list)
words_list.remove(question_two_file_name)
question_two_file_number = random.randint(1, MAX_FILES - 1)
question_two_num_words = random.randint(1, MAX_WORDS)
question_three_num_files_and_dirs = 0
question_four_letter = random.choice(string.ascii_lowercase)
question_four_num_files = 0
question_five_file_name = random.choice(words_list)
words_list.remove(question_five_file_name)
question_five_file_number = random.randint(1, MAX_FILES - 1)
question_five_word = ""
question_six_largest_file_size = 0
question_seven_num_directories = 0
question_seven_required_num_children = random.randint(0, 5)
question_eight_word = random.choice(words_list)
question_eight_word_frequency = 0
question_nine_num_dirs_no_immediate_file_children = 0
question_ten_word_frequency = 0
question_ten_frequency_map = {}

def create_file(file_path, words_to_add):
    fd = os.open(file_path, os.O_CREAT | os.O_WRONLY)
    for word in words_to_add:
        os.write(fd, word + "\n") # delimit the word list by newline

def gen_dir(file_path, dir_name):
    global directory_number
    global question_ten_frequency_map
    directory_number += 1
    if not dir_name in question_ten_frequency_map:
        question_ten_frequency_map[dir_name] = 0
    question_ten_frequency_map[dir_name] += 1
    os.mkdir(file_path) # Add the path

def gen_file(curr_dir):
    global question_one_file_name
    global question_one_file_number
    global question_one_word_in_file
    global question_eight_word_frequency
    global question_two_file_name
    global question_two_word_frequency
    global question_two_file_number
    global file_number
    global question_four_num_files
    global question_six_largest_file_size
    global question_ten_frequency_map
    file_name = random.choice(words_list)
    while os.path.exists(curr_dir + "/" + file_name):
        file_name = random.choice(words_list)
    if file_number == question_one_file_number:
        file_name = question_one_file_name
        fd = os.open(curr_dir + "/" + file_name, os.O_CREAT | os.O_WRONLY)
        os.write(fd, curr_dir + "/" + question_one_word_in_file)
        if question_one_word_in_file == question_eight_word:
            question_eight_word_frequency += 1

    elif file_number == question_two_file_number:
        file_name = question_two_file_name
        num_words = random.randint(1, MAX_WORDS)
        words_to_add = []
        for i in range(1, num_words):
            w = random.choice(words_list)
            if w == question_eight_word:
                question_eight_word_frequency += 1
            words_to_add.append(w)

        create_file(curr_dir + "/" + file_name, words_to_add)

    elif file_number == question_five_file_number:
        file_name = question_five_file_name
        num_words = random.randint(3, MAX_WORDS)
        words_to_add = []
        for i in range(1, num_words):
            w = random.choice(words_list)
            if w == question_eight_word:
                question_eight_word_frequency += 1
            words_to_add.append(w)
        create_file(curr_dir + "/" + file_name, words_to_add)
        question_five_word = w[-3]
    else:
        num_words = random.randint(3, MAX_WORDS)
        words_to_add = []
        for i in range(1, num_words):
            w = random.choice(words_list)
            if w == question_eight_word:
                question_eight_word_frequency += 1
            words_to_add.append(w)
        create_file(curr_dir + "/" + file_name, words_to_add)

    if file_name != "" and file_name[0] == question_four_letter:
        question_four_num_files += 1


    if not file_name in question_ten_frequency_map:
        question_ten_frequency_map[file_name] = 0
    question_ten_frequency_map[file_name] += 1
    statistics = os.stat(curr_dir + "/" + file_name)
    if statistics.st_size > question_six_largest_file_size:
        question_six_largest_file_size = statistics.st_size
    file_number += 1

bfs_q.put("./" + GAME_NAME)
directory_number += 1

while file_number < MAX_FILES:
    size = bfs_q.qsize()
    while size > 0:
        curr_dir = bfs_q.get()

        num_dirs = random.randint(1, MAX_DIR_CHILDREN)
        # random choice whether to generate directory or not
        cnt = 0
        while cnt < num_dirs and directory_number < MAX_DIRS:
            rand_word = random.choice(words_list)
            file_path = curr_dir + "/" + rand_word
            while os.path.exists(file_path):
                rand_word = random.choice(words_list)
                file_path = curr_dir + "/" + rand_word
            gen_dir(file_path, rand_word)
            bfs_q.put(file_path)
            cnt += 1
        num_files = random.randint(0, MAX_FILE_CHILDREN)
        cnt = 0
        while cnt < num_files and file_number < MAX_FILES:
            gen_file(curr_dir)
            print(str(file_number))
            cnt += 1

        if num_files == 0:
            question_nine_num_dirs_no_immediate_file_children += 1
        if num_dirs + num_files == question_seven_required_num_children:
            question_seven_num_directories += 1
        size -= 1
    depth += 1

question_three_num_files_and_dirs = file_number + directory_number
# Now simply parse to find max frequency num
maxKey = 0
for key in question_ten_frequency_map.keys():
    if key > maxKey:
        maxKey = key
question_ten_word_frequency = maxKey
