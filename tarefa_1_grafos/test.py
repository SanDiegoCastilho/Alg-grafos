import os
import commands

for i in range(120):
	print("--------Teste " + i + "--------")
	with open("../tarefa_1_solucoes/" + i + "_solucao.txt", "r") as file:
		stat, output = commands.getstatusoutput("cat {}_grafo.dl | ./teste.bin".format(i))

		if stat == 0:
			assert output == file.read().replace('\n', '')
		else:
			print("Command failed, here is the output")
