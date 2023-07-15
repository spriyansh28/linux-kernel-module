kernel_module = open('/proc/helloworldmodule')
string = kernel_module.readline()
print(string)
kernel_module.close()