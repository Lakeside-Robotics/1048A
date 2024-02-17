

def parse(func, var):
    
    if func == "mov":

        return "controller.add_action(autonomous_controller::moveBy(" + var + ", all));"
    
    if func == "spin":

        return "controller.add_action(autonomous_controller::turnBy(" + var + ", right, left));"
    
    if func == "outtake":

        return "controller.add_action(autonomous_controller::outtake(outtake));"

lines = []

with open("prog.txt", "r") as file:

    lines = [line.rstrip() for line in file]

with open("..\\src\\autonomous_parser.cpp", "w") as file:

    file.write("""
#include "autonomous_parser.h" \n
void ls::autonomous_parser::initController()
{
using namespace ls;
""")

    for line in lines:

        file.write(parse(line.split(":")[0], line.split(":")[-1]))
        file.write("\n")

    file.write("}")
            





        

