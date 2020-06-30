import click
import sys
import os
import socket
from pathlib import Path

def calc(len, file, it):

	# print(it)

	if len<=it:
		return None, it

	if ((len - it) <= 1024):
		l = file.read(len - it)
		it += len - it
	else:
		l = file.read(1024)
		it += 1024
	return l, it

@click.group()
def cli():
	pass

# Print iterations progress
def printProgressBar (iteration, total, prefix = '', suffix = '', decimals = 1, length = 100, fill = chr(9608), printEnd = "\r"):
    """
    Call in a loop to create terminal progress bar
    @params:
        iteration   - Required  : current iteration (Int)
        total       - Required  : total iterations (Int)
        prefix      - Optional  : prefix string (Str)
        suffix      - Optional  : suffix string (Str)
        decimals    - Optional  : positive number of decimals in percent complete (Int)
        length      - Optional  : character length of bar (Int)
        fill        - Optional  : bar fill character (Str)
        printEnd    - Optional  : end character (e.g. "\r", "\r\n") (Str)
    """
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + '-' * (length - filledLength)
    print('\r%s |%s| %s%% %s' % (prefix, bar, percent, suffix), end = printEnd)
    # Print New Line on Complete
    if iteration == total:
        print()

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

@click.command()
@click.option("--in", "-i", "in_file", required=True,
	help="input file",
	type=click.Path(exists=True, dir_okay=False, readable=True),
)
@click.option("--out-file", "-o", "out_file",
	help="destination file on server",
	type=click.Path(dir_okay=False),
)
@click.option("--destination_ip", "-d", "IP", required=True,
	help="IP server",
)
@click.option("--destination_port", "-p", "P", required=True,
	help="port server",
	type=int,
)
def receive(in_file, out_file, IP, P):
	s.connect((IP, P))
	print('connected')
	out_file += '\n'
	out_file = out_file.replace(' ', '_')
	s.send(out_file.encode())
	print('send1')
	name = os.path.basename(in_file)
	name += '\n'
	s.send(name.encode())
	print('send2')
	f = open(in_file,'rb')
	len = os.path.getsize(in_file)
	s.send(str(len).encode())
	# s.send(bin(len).encode())
	string_end = '\n\n'
	s.send(string_end.encode())
	print('start send file '+str(len))
	it = 0
	printProgressBar(0, len, prefix = 'Progress:', suffix = 'Complete', length = 50)
	l, it = calc(len, f, it)
	while (l):
		# print(l, it)
		try:
			s.send(l)
		except Exception as exc:
			print(exc)
			# it = it
		printProgressBar(it, len, prefix = 'Progress:', suffix = 'Complete', length = 50)
		l, it = calc(len, f, it)
	f.close()
	print("Done Sending")



cli.add_command(receive)

if __name__ == '__main__':
	cli()
