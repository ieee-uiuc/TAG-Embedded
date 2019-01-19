import json as j
import hashlib as hl
import os
import shutil
import queue
import requests
import random
import json
import hashlib
import string
import argparse as ap

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

def delete(delete_name):
    if os.geteuid() == "root":
        print("Don't run as root")
    try:
        shutil.rmtree(delete_name)
        print("Deleting old game")
    except Exception as e:
        pass

def check(check_name):
    pass # TODO create check function

def create(game_dir, max_dir_children, max_file_children, max_files, max_dirs, max_words):
    GAME_NAME = game_dir
    MAX_DIR_CHILDREN = max_dir_children
    MAX_FILE_CHILDREN = max_file_children
    MAX_FILES = max_files
    MAX_DIRS = max_dirs
    MAX_WORDS = max_words
    WORD_SITE = "http://svnweb.freebsd.org/csrg/share/dict/words?view=co&content-type=text/plain" # Name of site to get words from

    if os.geteuid() == "root":
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
    bfs_q = queue.Queue(maxsize=0)
    resp = requests.get(WORD_SITE) # Get words for use in game
    words_list = [x.decode("utf-8").lower() for x in resp.content.splitlines()] #convert words to lowercase


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
            os.write(fd, str.encode(word + "\n")) # delimit the word list by newline

    def gen_dir(file_path, dir_name):
        nonlocal directory_number
        nonlocal question_ten_frequency_map
        directory_number += 1
        if not dir_name in question_ten_frequency_map:
            question_ten_frequency_map[dir_name] = 0
        question_ten_frequency_map[dir_name] += 1
        os.mkdir(file_path) # Add the path

    def gen_file(curr_dir):
        nonlocal question_one_file_name
        nonlocal question_one_file_number
        nonlocal question_one_word_in_file
        nonlocal question_eight_word_frequency
        nonlocal question_two_file_name
        nonlocal question_two_file_number
        nonlocal file_number
        nonlocal question_four_num_files
        nonlocal question_six_largest_file_size
        nonlocal question_ten_frequency_map
        file_name = random.choice(words_list)
        while os.path.exists(curr_dir + "/" + file_name):
            file_name = random.choice(words_list)
        if file_number == question_one_file_number:
            file_name = question_one_file_name
            fd = os.open(curr_dir + "/" + file_name, os.O_CREAT | os.O_WRONLY)
            os.write(fd, str.encode(curr_dir + "/" + question_one_word_in_file))
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
                rand_w = random.choice(words_list)
                new_file_path = curr_dir + "/" + rand_w

                while os.path.exists(new_file_path):
                    rand_w = random.choice(words_list)
                    new_file_path = curr_dir + "/" + rand_w
                gen_dir(new_file_path, rand_w)
                bfs_q.put(new_file_path)
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
    maxVal = 0
    for val in question_ten_frequency_map.values():
        if val > maxVal:
            maxVal = val
    question_ten_word_frequency = maxVal

    # Last step is to hash and store the answers
    # Create hidden dir
    cache_name = "." + game_dir + "cache.json"
    json_dict = {}
    json_dict["cq"] = h1.sha256("q1").hexdigest()
    json_dict["q1"] = "What is the word in the file named {}".format(str(question_one_file_name))
    json_dict["a1"] = hl.sha256(str(question_one_word_in_file)).hexdigest()
    json_dict["q2"] = "How many words does the file named {} have?".format(str(question_two_file_name))
    json_dict["a2"] = hl.sha256(str(question_two_num_words)).hexdigest()
    json_dict["q3"] = "How many files and directories are there all together including the initial dir?"
    json_dict["a3"] = hl.sha256(str(question_three_num_files_and_dirs)).hexdigest()
    json_dict["q4"] = "How many files start with the letter {}? (Files not dirs)".format(str(question_four_letter))
    json_dict["a4"] = hl.sha256(str(question_four_num_files)).hexdigest()
    json_dict["q5"] = "What is the word on the third to last line of the file named {}?".format(str(question_five_file_name))
    json_dict["a5"] = hl.sha256(str(question_five_word)).hexdigest()
    json_dict["q6"] = "What is the size of the largest file? (In kilobytes)"
    json_dict["a6"] = hl.sha256(str(question_six_largest_file_size)).hexdigest()
    json_dict["q7"] ="How many directories have {} many children?".format(str(question_seven_required_num_children))
    json_dict["a7"] = hl.sha256(str(question_seven_num_directories)).hexdigest()
    json_dict["q8"] = "What is the frequency of the word {} in the files of the directory tree?".format(str(question_eight_word_frequency))
    json_dict["a8"] = hl.sha256(str(question_eight_word_frequency)).hexdigest()
    json_dict["q9"] = "How many directories have no immediate file children?"
    json_dict["a9"] = hl.sha256(str(question_nine_num_dirs_no_immediate_file_children)).hexdigest()
    json_dict["q10"] = "What is the frequency of the word appearing the maximum number of times in files, as file names, and as directory names?"
    json_dict["a10"] = hl.sha256(str(question_ten_word_frequency)).hexdigest()
    json_str = j.dump(json_dict)
    outfile = open(cache_name, "w")
    outfile.write(json_str)
    outfile.close()
    print("Generation finished! The file tree {} has been created for you".format(GAME_NAME))
if __name__ == "__main__":
    parser = ap.ArgumentParser(description="A file tree search game for Linux")
    subparsers = parser.add_subparsers()
    parser_create = subparsers.add_parser("create", help="Create a new linux game instance")
    parser_create.add_argument('--name', type=str, default="linux_game", dest="create_name", help='The created game instance directory')
    parser_create.add_argument('-f', type=int, default=1000, dest="max_files", help="The maximum number of files allowed in the tree")
    parser_create.add_argument('-d', type=int, default=2000, dest="max_dirs", help="The maximum number of directories allowed in the tree")
    parser_create.add_argument('-w', type=int, default=500, dest="max_words", help="The maximum number of words allowed in a file")
    parser_create.add_argument('--fc', type=int, default=4, dest="max_file_children", help="The maximum number of files a directory can have")
    parser_create.add_argument('--dc', type=int, default=6, dest="max_dir_children", help="The maximum number of directory children a directory can have")
    parser_delete = subparsers.add_parser("delete", help="Delete a linux game instance")
    parser_delete.add_argument("--name", type=str, default="linux_game", dest="delete_name", help="Name of the instance to delete")
    parser_check = subparsers.add_parser("check", help="Check your answers to the linux game questions")
    parser_check.add_argument("--name", type=str, default="linux_game", dest="check_name", help="Name of the game instance to check")

    args = parser.parse_args()
    if args.create:
        create(args.create_name, args.max_dir_children, args.max_file_children, args.max_files, args.max_dirs, args.max_words)
    elif args.delete:
        delete(args.delete_name)
    elif args.check:
        check(args.check_name)
