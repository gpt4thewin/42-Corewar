#! /usr/bin/python3

# Binaries path:
ZAZ_VM = "/Users/mbakhti/Desktop/Corewar/resources/diff_tool/bin/zaz_corewar"
USR_VM = "/Users/mbakhti/Desktop/Corewar/vm/corewar"

# Results path:
RESULTS_DIRECTORY = "/Users/mbakhti/Desktop/Corewar/resources/diff_tool/results"

import shutil, os, sys, argparse

def check_user_settings():
	if not os.path.exists(USR_VM) or not os.path.isfile(USR_VM):
		exit(print("error: " + USR_VM + ": Binary missing, or not a binary, change USR_VM value in script."))
	if not os.path.exists(ZAZ_VM) or not os.path.isfile(ZAZ_VM):
		exit(print("error: " + ZAZ_VM + ": Binary missing, or not a binary, change ZAZ_VM value in script."))
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

def	main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--dump", type=int, help="dump after DUMP cycles")
	parser.add_argument('champion', help='compiled champion to load in vm', nargs='+')
	args = parser.parse_args()
	if (args.dump):
		zaz_out = RESULTS_DIRECTORY + "/zaz/" + str(args.dump) + ".dump"
		usr_out = RESULTS_DIRECTORY + "/usr/" + str(args.dump) + ".dump"
		os.system(ZAZ_VM + " -d " + str(args.dump)+ " " + " ".join(args.champion) + " > " + zaz_out)
		os.system(USR_VM + " -d " + str(args.dump)+ " " + " ".join(args.champion) + " > " + usr_out)
		if not os.system("diff " + usr_out + " " + zaz_out):
			print("No diff after {} cycles for champions: {}".format(args.dump, args.champion))
	else:
		zaz_out = RESULTS_DIRECTORY + "/zaz/vm.dump"
		usr_out = RESULTS_DIRECTORY + "/usr/vm.dump"
		os.system(ZAZ_VM + " " + " ".join(args.champion) + " > " + zaz_out)
		os.system(USR_VM + " " + " ".join(args.champion) + " > " + usr_out)
		if not os.system("diff " + usr_out + " " + zaz_out):
			print("No diff for champions: {}".format(args.champion))
check_user_settings()
initialise_results_directory()
main()
