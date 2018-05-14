from subprocess import Popen, PIPE

for i in range(120):
	print("--------Teste %d--------" % i)
	with open("../tarefa_1_solucoes/%d_solucao.txt" % i, "r") as file:
		output = Popen(['./test.bin < %d_grafo.dl' % i], stdout=PIPE, shell=True).communicate()[0].decode("utf-8")
		print(output == file.read())

