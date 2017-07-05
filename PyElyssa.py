from __future__ import division
from sympy import *

class EQUATION:
    def __init__(self, eq, v):
        self.eq = eq
        self.v = v


def read_var(filename):
	index = {}
	var_file = open(filename,'r')
	i = 0
	for line in var_file:
		for word in line.split():
			index[word] = i
			i += 1	
	a = ''
	for i in range(0, len(index)):
		a += 'v['+str(i)+'] '
	v = list(symbols(a))
	return (v,index)

def read_eq(filename):
    equation, copied_equation = [],[]
    eq_file = open(filename, 'r')
    for line in eq_file:
        words = line.split()
        eq = sympify(words[0]+'-('+words[1]+')')
        varlist = list(symbols(' '.join(words[2:])))
        equation.append(EQUATION(eq, varlist))
        copied_equation.append(EQUATION(eq, varlist))
    return equation, copied_equation

def initialize1(eq, data):
    known = {}
    parent = {}
    n = data[1]
    for i in range(0, n):
        known[symbols(data[i*2+2])] = float(data[i*2+3])
    	parent[symbols(data[i*2+2])] = -1
    for i in range(0, len(eq)):
		for j in known.keys():
			if j in eq[i].v:
				eq[i].eq = eq[i].eq.subs(j, known[j])
    return eq, known, parent

def initialize2(eq1, eq2):
	eq1, known1 = initialize1(eq1, "Number of knowns (for the first object)=")
	eq2, known2 = initialize1(eq2, "Number of knowns (for the second object)=")
	cond_eq = []
	a = raw_input('Any other conditions? y/n')
	if a == 'y':
		n = int(raw_input('Number of conditions='))
		print "Write them one at a line.\nFormat: LHS <space> = <space> RHS <space> Variables(each seperated by a space)"
		for i in range(0, n):
			words = raw_input().split()
			eq = sympify(words[0]+'-('+words[2]+')')
			varlist = list(symbols(' '.join(words[3:])))
			cond_eq.append(EQUATION(eq, varlist))
	return eq1, eq2, dict(known1.items()+known2.items()), cond_eq

def update_eq(eq, var, val):
	for i in range(0, len(eq)):
		if var in eq[i].v:
			eq[i].eq = eq[i].eq.subs(var, val)
	return eq

def find(eq, known, parent):
    index = -1;
    for i in eq:
        index += 1
        counter = 0
        variable = ''
        for j in i.v:
            if j not in known:
                counter += 1
                variable = j
        if counter == 1:
            solutions = solve(i.eq, variable)
            if solutions:
				known[variable] = solutions[-1]
				parent[variable] = index
				eq = update_eq(eq, variable,  solutions[-1])
				i = eq[0]
				index = -1
    return eq, known, parent

def find_related_eq(eq, known, cond_eq, cond_var):
    for i in eq:
        unknown_var = 0
        var_in_cond_var = 0
        variable = ''
        for j in i.v:
            if j not in known:
                unknown_var += 1
                if j in cond_var:
                    var_in_cond_var += 1
                variable = j
        if unknown_var == var_in_cond_var and var_in_cond_var != 0:
            cond_eq.append(i)
    return cond_eq

def SolveProblem(data):
	if data[0] == 's':
		eq, copied_eq = read_eq('eq.txt')
		eq, known, parent = initialize1(eq, data)
		unknown = symbols(data[-1])
		eq, known, parent = find(eq, known, parent)
		if unknown in known.keys():
			print  copied_eq[parent[unknown]].eq
			return known[unknown]
		else:
			return "Can't solve\n"
	elif mode == 'm' or mode == 'M':
		eq1 = read_eq('eq1.txt')
		eq2 = read_eq('eq2.txt')
		eq1, eq2, known, cond_eq = initialize2(eq1, eq2)
		unknown = symbols(raw_input("What to find="))
		eq1, known = find(eq1, known)
		eq2, known = find(eq2, known)
		
		for i in known.keys():
			cond_eq = update_eq(cond_eq, i, known[i])
		cond_var = []
		for i in cond_eq:
			for j in i.v:
				if j not in cond_var:
					cond_var.append(j)
		cond_eq = find_related_eq(eq1, known, cond_eq, cond_var)
		cond_eq = find_related_eq(eq2, known, cond_eq, cond_var)
		final_equations = []
		for i in cond_eq:
			final_equations.append(i.eq)
		solutions = solve(final_equations, cond_var, dict = True)
		if solutions:
			solutions = solutions[-1]
			for variable in solutions.keys():
				known[variable] = solutions[variable]
				eq1 = update_eq(eq1, variable, solutions[variable])
				eq2 = update_eq(eq2, variable, solutions[variable])
		eq1, known = find(eq1, known)
		eq2, known = find(eq2, known)
		if unknown in known.keys():
			print unknown, '=', known[unknown]
		else:
			print "Can't solve\n"

print SolveProblem(['s', 3, 'u', '10', 'a', '3', 't', '4', 'v'])

"""
for equation in equations:
    unknown = 0
    for v in equation.list:
    	if v not in knowns:
    		unknown += 1 
    if unknown == 1:
        variable = solve(equation)
        knowns.add(variable)
        equation = equations[0]
"""
