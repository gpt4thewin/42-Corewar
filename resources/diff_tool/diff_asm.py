#! /usr/bin/python3

# Binaries path:
USR_ASM = "/Users/mbakhti/Desktop/Corewar/asm/asm"
ZAZ_ASM = "/Users/mbakhti/Desktop/Corewar/resources/diff_tool/bin/zaz_asm"

# Champions path:
CHAMPIONS_DIRECTORY = "/Users/mbakhti/Desktop/Corewar/resources/diff_tool/champions/error"

# Results path:
RESULTS_DIRECTORY = "/Users/mbakhti/Desktop/Corewar/resources/diff_tool/results"

# Colors macros:
RED		= "\x1b[31m"
GREEN	= "\x1b[32m"
BLUE	= "\x1b[34m"
YELLOW	= "\x1b[33m"
RESET	= "\x1b[0m"

import shutil, os, sys

def check_user_settings():
	if not os.path.exists(USR_ASM) or not os.path.isfile(USR_ASM):
		exit(print("error: " + USR_ASM + ": Binary missing, or not a binary, change USR_ASM value in script."))
	if not os.path.exists(ZAZ_ASM) or not os.path.isfile(ZAZ_ASM):
		exit(print("error: " + ZAZ_ASM + ": Binary missing, or not a binary, change ZAZ_ASM value in script."))
	if not os.path.exists(CHAMPIONS_DIRECTORY) or not os.path.isdir(CHAMPIONS_DIRECTORY):
		exit(print("error: " + CHAMPIONS_DIRECTORY + ": Directory missing, or not a directory, change CHAMPIONS_DIRECTORY value in script."))
	if os.path.exists(RESULTS_DIRECTORY) and not os.path.isdir(RESULTS_DIRECTORY):
		exit(print("error: " + RESULTS_DIRECTORY + ": File exists, change RESULTS_DIRECTORY variable in script."))

def	initialise_results_directory():
	if not os.path.exists(RESULTS_DIRECTORY):
		os.mkdir(RESULTS_DIRECTORY)
	if os.path.exists(RESULTS_DIRECTORY + "/usr") and os.path.isdir(RESULTS_DIRECTORY + "/usr"):
		shutil.rmtree(RESULTS_DIRECTORY + "/usr")
	elif os.path.exists(RESULTS_DIRECTORY + "/usr") and not os.path.isdir(RESULTS_DIRECTORY + "/usr"):
		exit(print("error: " + RESULTS_DIRECTORY + "/usr: File exists, change RESULTS_DIRECTORY variable in script."))
	os.mkdir(RESULTS_DIRECTORY + "/usr")
	if os.path.exists(RESULTS_DIRECTORY + "/zaz") and os.path.isdir(RESULTS_DIRECTORY + "/zaz"):
		shutil.rmtree(RESULTS_DIRECTORY + "/zaz")
	elif os.path.exists(RESULTS_DIRECTORY + "/zaz") and not os.path.isdir(RESULTS_DIRECTORY + "/zaz"):
		exit(print("error: " + RESULTS_DIRECTORY + "/zaz: File exists, change RESULTS_DIRECTORY variable in script."))
	os.mkdir(RESULTS_DIRECTORY + "/zaz")

def exec_asm(asm, user, champion):
		result_dir = RESULTS_DIRECTORY + user
		stdout_file = result_dir + champion + ".out"
		stderr_file = result_dir + champion + ".err"
		dump_file = result_dir + champion + ".dump"
		cor_file = CHAMPIONS_DIRECTORY + "/" + champion + ".cor"
		s_file = CHAMPIONS_DIRECTORY + "/" +  champion + ".s"
		os.system(asm + " " + s_file + " > " + stdout_file + " 2>" + stderr_file)
		os.system("hexdump -vC " + cor_file + " > " + dump_file + " 2>/dev/null")
		os.system("mv " + cor_file + " " + result_dir + " 2>/dev/null")

def diff_all():
	print(BLUE + "------------ DIFF ASM ------------" + RESET)
	for filename in os.listdir(CHAMPIONS_DIRECTORY):
		champion = os.path.splitext(filename)[0]
		exec_asm(ZAZ_ASM, "/zaz/", champion)
		exec_asm(USR_ASM, "/usr/", champion)
		zaz = RESULTS_DIRECTORY + "/zaz/" + champion
		usr = RESULTS_DIRECTORY + "/usr/" + champion
		zazout = zaz + ".out"
		usrout = usr + ".out"
		zazerr = zaz + ".err"
		usrerr = usr + ".err"
		zazdump = zaz + ".dump"
		usrdump = usr + ".dump"
		if os.system("diff " + usrout + " " + zazout + " > /dev/null 2>&1") or os.system("diff " + usrerr + " " + zazerr + " > /dev/null 2>&1"):
			COLOR = YELLOW
		else:
			COLOR = GREEN
		if os.system("diff " + usrdump + " " + zazdump + " > /dev/null 2>&1"):
			COLOR = RED
		print(COLOR + champion + RESET)
	print(BLUE + "----------------------------------" + RESET)

def diff_one(champion):
	print(BLUE + "--- DIFF " + champion.upper() + " ---" + RESET)
	if not os.path.exists(CHAMPIONS_DIRECTORY + "/" + champion + ".s"):
		print("error: " + CHAMPIONS_DIRECTORY + "/" + champion + ".s" + ": Source file missing.")
	else:
		print(YELLOW + open(CHAMPIONS_DIRECTORY + "/" + champion + ".s", 'r').read(), end = RESET)
		exec_asm(ZAZ_ASM, "/zaz/", champion)
		exec_asm(USR_ASM, "/usr/", champion)
		zaz = RESULTS_DIRECTORY + "/zaz/" + champion
		usr = RESULTS_DIRECTORY + "/usr/" + champion
		zazout = zaz + ".out"
		usrout = usr + ".out"
		zazerr = zaz + ".err"
		usrerr = usr + ".err"
		zazdump = zaz + ".dump"
		usrdump = usr + ".dump"
		print("STDOUT:")
		if not os.system("diff " + usrout + " " + zazout):
			print(open(usrout).read(), end = "")
		print("STDERR:")
		if not os.system("diff " + usrerr + " " + zazerr):
			print(open(usrerr).read(), end = "")
		print("BINARY:")
		if not os.system("diff " + usrdump + " " + zazdump):
			print(open(usrdump).read(), end = "")

check_user_settings()
initialise_results_directory()
if not len(sys.argv) > 1:
	diff_all()
elif len(sys.argv) == 2 and sys.argv[1] == "-v":
	for filename in os.listdir(CHAMPIONS_DIRECTORY):
		champion = os.path.splitext(filename)[0]
		diff_one(champion)
else:
	for filename in sys.argv[1:]:
		diff_one(filename)
