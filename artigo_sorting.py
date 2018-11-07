# -*- coding: utf-8 -*-
"""
Created on Sat Oct 27 12:53:04 2018

@author: Felipe Levez
"""

from random import randint
import time
import matplotlib.pyplot as plt
import numpy as np
import sys


class Sorting_algorithms(object):
    def __init__(self, name, order, leng):
        self.name = name
        self.duration = 0.0
        self.movement = 0
        self.comparisons = 0
        self.order = order
        self.leng = leng
        self.vector = []

    
    def move(self, i, j):
        aux = self.vector[i]
        self.vector[i] = self.vector[j]
        self.vector[j] = aux
        
    
    def generate_values(self):
        if self.order=='Random':
            for i in range(0, self.leng):
                self.vector.append(randint(0, 1000))
        elif self.order=='Ascending':
            for i in range(0, self.leng):
                self.vector.append(i)
        else:
            for i in range(self.leng, 0, -1):
                self.vector.append(i)
    
    
    def copy_values(self, other):
        for i in range(0, other.leng):
            self.vector.append(other.vector[i])
     
    
    def insertion_sort(self):
        start = time.time()
        for i in range(1,len(self.vector)):
            j = i
            while j>0:
                self.comparisons = self.comparisons + 1
                if self.vector[j-1] > self.vector[j]:
                    self.move(j, j-1)
                    self.movement = self.movement + 1
                j = j-1
        final= time.time()
        self.duration = (final - start)
        
    
    def selection_sort(self):
        start = time.time()
        for i in range(0, self.leng - 1):
            minimum = i
            for j in range(i+1, self.leng):
                self.comparisons = self.comparisons + 1
                if self.vector[j] < self.vector[minimum]:
                    minimum = j
            self.comparisons = self.comparisons + 1
            if i != minimum:
                self.move(minimum, i)
                self.movement = self.movement + 1
        final= time.time()
        self.duration = (final - start)
    
    
    def bubble_sort(self):
        start = time.time()
        for i in range(self.leng-1, 0, -1):
            for j in range(0, i):
                self.comparisons = self.comparisons + 1
                if self.vector[j] > self.vector[j + 1]:
                    self.move(j, j+1)
                    self.movement = self.movement + 1
        final= time.time()
        self.duration = (final - start)
    
    
    def shell_sort(self):
        start = time.time()
        i = (self.leng - 1) / 2
        while i != 0:
            while True:
                key = 1
                for k in range(0, self.leng - int(i)):
                    self.comparisons = self.comparisons + 1
                    if(self.vector[k] > self.vector[k + int(i)]):
                        self.move(k, k+int(i))
                        key = 0
                        self.movement = self.movement + 1
                self.comparisons = self.comparisons + 1
                if key != 0:
                    break
            i = i / 2
        final= time.time()
        self.duration = (final - start)
    
    
    def heapify(self, n, i):
        
        largest = i
        l = 2 * i + 1
        r = 2 * i + 2
        self.comparisons = self.comparisons+1
        if l < n and self.vector[i] < self.vector[l]:
            largest = l
        self.comparisons = self.comparisons+2
        if r < n and self.vector[largest] < self.vector[r]:
            largest = r
        self.comparisons = self.comparisons+2
        if largest != i:
            self.vector[i],self.vector[largest] = self.vector[largest],self.vector[i]
            self.movement = self.movement+1
            self.heapify(n, largest)
    
    
    def heap_sort(self):
        n = self.leng
        for i in range(n, -1, -1):
            self.heapify(n, i)
        for i in range(n-1, 0, -1):
            self.vector[i], self.vector[0] = self.vector[0], self.vector[i]
            self.movement = self.movement+1
            self.heapify(i, 0)
    
    
    def comb_sort(self):
        start = time.time()
        gap = self.leng
        swaps = True
        while gap > 1 or swaps:
            gap = max(1, int(gap / 1.25)) # minimum gap is 1
            swaps = False
            for i in range(self.leng - gap):
                j = i+gap
                self.comparisons = self.comparisons+1
                if self.vector[i] > self.vector[j]:
                    self.vector[i], self.vector[j] = self.vector[j], self.vector[i]
                    self.movement = self.movement+1
                    swaps = True
        final = time.time()
        self.duration = final-start
    
    
    def countingSort(self, exp1):
        n = self.leng
        output = [0] * (n)
        count = [0] * (10)
        for i in range(0, n):
            self.comparisons = self.comparisons+1
            index = int(self.vector[i]/exp1)
            count[ int((index)%10) ] += 1
        for i in range(1,10):
            self.comparisons = self.comparisons+1
            count[i] += count[i-1]
        i = n-1
        while i>=0:
            self.comparisons = self.comparisons+1
            index = int(self.vector[i]/exp1)
            output[ count[ int((index)%10) ] - 1] = self.vector[i]
            self.movement = self.movement+1
            count[ int((index)%10) ] -= 1
            i -= 1
        i = 0
        for i in range(0,self.leng):
            self.comparisons = self.comparisons+1
            self.vector[i] = output[i]
            self.movement = self.movement+1
    
    
    def merge(self, left, right): 
    
        self.comparisons+=1
        if not len(left):
            return left  
        self.comparisons+=1
        if not len(right):
            return right
        result = [] 
        i, j = 0, 0
        while True:
            self.comparisons+=1
            if not (len(result) < len(left) + len(right)): 
                break
            self.comparisons+=1
            if left[i] < right[j]: 
                result.append(left[i]) 
                self.movement+=1
                i+= 1
            else: 
                result.append(right[j]) 
                self.movement+=1
                j+= 1
                
            self.comparisons+=2
            if i == len(left) or j == len(right): 
                result.extend(left[i:] or right[j:])
                break 
      
        return result 
    
    
    def merge_sort(self, vector):
        self.comparisons+=1
        if len(vector) < 2: 
            return vector
      
        middle = len(vector)//2
        left = self.merge_sort(vector[:middle]) 
        right = self.merge_sort(vector[middle:]) 
      
        return self.merge(left, right) 
    
    
    def partition(self,l,h): 
        i = ( l - 1 ) 
        x = self.vector[h] 
        
        for j in range(l , h): 
            self.comparisons+=1
            if self.vector[j] <= x: 
                i = i+1
                self.vector[i],self.vector[j] = self.vector[j],self.vector[i] 
                self.movement+=1
        
        self.movement+=1
        self.vector[i+1],self.vector[h] = self.vector[h],self.vector[i+1] 
        return (i+1) 
        
    def quick_sort(self,l,h): 
        
        size = h - l + 1
        stack = [0] * (size) 
        
        top = -1
        
        top = top + 1
        stack[top] = l 
        top = top + 1
        stack[top] = h 
        
        while True: 
            self.comparisons+=1
            if not top>=0:
                break
            h = stack[top] 
            top = top - 1
            l = stack[top] 
            top = top - 1
        
            p = self.partition( l, h ) 
                
            self.comparisons+=1
            if p-1 > l: 
                top = top + 1
                stack[top] = l 
                top = top + 1
                stack[top] = p - 1
            
            self.comparisons+=1
            if p+1 < h: 
                top = top + 1
                stack[top] = p + 1
                top = top + 1
                stack[top] = h 
        
                        
    
    def radix_sort(self):
        max_value = max(self.vector)
        exp = 1
        while max_value/exp > 0:
            self.comparisons = self.comparisons+1
            self.countingSort(exp)
            exp *= 10
            

def sorting(begin, end):
    for j in range(0, 30):
        
        print(j)
        print(' - Inicio do Loop')
        
        copier_values(begin, end)
        
        for i in range(begin, end):
            selection[i].selection_sort()
            bubble[i].bubble_sort()
            insertion[i].insertion_sort()
            shell[i].shell_sort()
            
            comb[i].comb_sort()
            
            start = time.time()
            radix[i].radix_sort()
            final = time.time()
            radix[i].duration = final-start
            
            start = time.time()
            heap[i].heap_sort()
            final = time.time()
            heap[i].duration = final-start
            
            start = time.time()
            quick[i].quick_sort(0, quick[i].leng-1)
            final = time.time()
            quick[i].duration = final-start
            
            start = time.time()
            merge[i].vector = merge[i].merge_sort(merge[i].vector)
            final = time.time()
            merge[i].duration = final-start
            
            save_results(i)
        
            
        print(' - Fim do Loop')
        clean_vector(begin, end)
    


def save_results(i):

    results_selection[i][0] += selection[i].duration/30
    results_selection[i][1] += selection[i].movement/30
    results_selection[i][2] += selection[i].comparisons/30
    
    results_bubble[i][0] += bubble[i].duration/30
    results_bubble[i][1] += bubble[i].movement/30
    results_bubble[i][2] += bubble[i].comparisons/30
    
    results_insertion[i][0] += insertion[i].duration/30
    results_insertion[i][1] += insertion[i].movement/30
    results_insertion[i][2] += insertion[i].comparisons/30
    
    results_shell[i][0] += shell[i].duration/30
    results_shell[i][1] += shell[i].movement/30
    results_shell[i][2] += shell[i].comparisons/30
    
    results_comb[i][0] += comb[i].duration/30
    results_comb[i][1] += comb[i].movement/30
    results_comb[i][2] += comb[i].comparisons/30
    
    results_radix[i][0] += radix[i].duration/30
    results_radix[i][1] += radix[i].movement/30
    results_radix[i][2] += radix[i].comparisons/30
    
    results_heap[i][0] += heap[i].duration/30
    results_heap[i][1] += heap[i].movement/30
    results_heap[i][2] += heap[i].comparisons/30
    
    results_quick[i][0] += quick[i].duration/30
    results_quick[i][1] += quick[i].movement/30
    results_quick[i][2] += quick[i].comparisons/30
    
    results_merge[i][0] += merge[i].duration/30
    results_merge[i][1] += merge[i].movement/30
    results_merge[i][2] += merge[i].comparisons/30
    


def clean_vector(begin, end):
    for i in range(begin, end):
        del selection[i].vector[:]
        del bubble[i].vector[:]
        del insertion[i].vector[:]
        del shell[i].vector[:]
        del comb[i].vector[:]
        del radix[i].vector[:]
        del heap[i].vector[:]
        del quick[i].vector[:]
        del merge[i].vector[:]


def create_sorting_algorithm(order, leng):
    selection.append(Sorting_algorithms('Selection Sort', order, leng))
    insertion.append(Sorting_algorithms('Insertion Sort', order, leng))
    bubble.append(Sorting_algorithms('Bubble Sort', order, leng))
    shell.append(Sorting_algorithms('Shell Sort', order, leng))
    quick.append(Sorting_algorithms('Quick Sort', order, leng))
    merge.append(Sorting_algorithms('Merge Sort', order, leng))
    heap.append(Sorting_algorithms('Heap Sort', order, leng))
    comb.append(Sorting_algorithms('Comb Sort', order, leng))
    radix.append(Sorting_algorithms('Radix Sort', order, leng))


def copier_values(begin, end):           
    for i in range(begin, end):
        selection[i].generate_values()
        bubble[i].copy_values(selection[i])
        insertion[i].copy_values(selection[i])
        shell[i].copy_values(selection[i])
        quick[i].copy_values(selection[i])
        merge[i].copy_values(selection[i])
        heap[i].copy_values(selection[i])
        comb[i].copy_values(selection[i])
        radix[i].copy_values(selection[i])            
            
   

    

def play():   
    create_sorting_algorithm('Descending', 10)
    create_sorting_algorithm('Descending', 100)         
    create_sorting_algorithm('Descending', 1000)
    create_sorting_algorithm('Descending', 50000)
        
    create_sorting_algorithm('Ascending', 10)
    create_sorting_algorithm('Ascending', 100)         
    create_sorting_algorithm('Ascending', 1000)
    create_sorting_algorithm('Ascending', 50000)

    create_sorting_algorithm('Random', 10)
    create_sorting_algorithm('Random', 100)         
    create_sorting_algorithm('Random', 1000)
    create_sorting_algorithm('Random', 50000)
    
    sorting(0, 12)


selection = []
insertion=[]
bubble = []
shell = []
quick = []
merge = []
heap = []
comb = []
radix = []            
            

results_selection = np.zeros((12,3))
results_insertion = np.zeros((12,3))
results_bubble = np.zeros((12,3))
results_shell = np.zeros((12,3))
results_quick = np.zeros((12,3))
results_merge = np.zeros((12,3))
results_heap = np.zeros((12,3))
results_comb = np.zeros((12,3))
results_radix = np.zeros((12,3))

play()
            


def create_subplots(title, text_x, text_y, vet_yaxis, position):
    
    plt.subplot(3, 3, position)
    plt.title(title)
    
    plt.plot([10, 100, 1000, 50000],vet_yaxis[:4], 'r^', label='Vetor decrescente')
    plt.plot([10, 100, 1000, 50000],vet_yaxis[:4], 'r--')
    
    plt.plot([10, 100, 1000, 50000],vet_yaxis[4:8], 'bo', label='Vetor crescente')
    plt.plot([10, 100, 1000, 50000],vet_yaxis[4:8], 'b--')
    
    plt.plot([10, 100, 1000, 50000],vet_yaxis[8:], 'y*', label='Vetor aleatório')
    plt.plot([10, 100, 1000, 50000],vet_yaxis[8:], 'y--')
    
    plt.xlabel(text_x)
    plt.ylabel(text_y)
    plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)

    
    


def generate_y(result, value):   
    y=[]
    for i in range(0, 12):
        y.append(result[i][value])    
    return y


def generate_figure(text_x, text_y, value_position):
    
    create_subplots('Selection Sort', text_x,text_y, generate_y(results_selection, value_position), 1)
    create_subplots('Bubble Sort', text_x,text_y, generate_y(results_bubble, value_position), 2)
    create_subplots('Insertion Sort', text_x,text_y, generate_y(results_insertion, value_position), 3)
    create_subplots('Quick Sort', text_x,text_y, generate_y(results_quick, value_position), 4)
    create_subplots('Merge Sort', text_x,text_y, generate_y(results_merge, value_position), 5)
    create_subplots('Shell Sort', text_x,text_y, generate_y(results_shell, value_position), 6)
    create_subplots('Heap Sort', text_x,text_y, generate_y(results_heap, value_position), 7)
    create_subplots('Comb Sort', text_x,text_y, generate_y(results_comb, value_position), 8)
    create_subplots('Radix Sort', text_x,text_y, generate_y(results_radix, value_position), 9)
    
    
    plt.show()


fig = plt.figure(figsize=(20, 15))
fig.subplots_adjust(hspace=0.4, wspace=1.1)
generate_figure('Quantidade de valores','Duração (s)',0)

fig = plt.figure(figsize=(20, 15))
fig.subplots_adjust(hspace=0.4, wspace=1.1)
generate_figure('Quantidade de valores','Movimentos',1)

fig = plt.figure(figsize=(20, 15))
fig.subplots_adjust(hspace=0.4, wspace=1.1)
generate_figure('Quantidade de valores','Comparações',2)



    
results_heap_best = np.zeros((12,3))
results_comb_best = np.zeros((12,3))
results_merge_best = np.zeros((12,3))

def play_best():   

    best_heap = []
    best_merge = []
    best_comb = []

    
    best_heap.append(Sorting_algorithms('Heap Sort', 'Descending', 1000000))
    best_heap.append(Sorting_algorithms('Heap Sort', 'Ascending', 1000000))
    best_heap.append(Sorting_algorithms('Heap Sort', 'Random', 1000000))
    
    best_merge.append(Sorting_algorithms('Merge Sort', 'Descending', 1000000))
    best_merge.append(Sorting_algorithms('Merge Sort', 'Ascending', 1000000))
    best_merge.append(Sorting_algorithms('Merge Sort', 'Random', 1000000))
    
    best_comb.append(Sorting_algorithms('Comb Sort', 'Descending', 1000000))
    best_comb.append(Sorting_algorithms('Comb Sort', 'Ascending', 1000000))
    best_comb.append(Sorting_algorithms('Comb Sort', 'Random', 1000000))
    
    for j in range(0, 30):
        
        print(j)
        print(' - Inicio do Loop')
        
        for i in range(0, 3):
            best_heap[i].generate_values()
            best_comb[i].copy_values(best_heap[i])
            best_merge[i].copy_values(best_heap[i])
        
        for i in range(0, 3):
            
            best_comb[i].comb_sort()
            
            start = time.time()
            best_heap[i].heap_sort()
            final = time.time()
            best_heap[i].duration = final-start
            
            start = time.time()
            best_merge[i].vector = best_merge[i].merge_sort(best_merge[i].vector)
            final = time.time()
            best_merge[i].duration = final-start
            
            results_heap_best[i][0] += best_heap[i].duration/30
            results_heap_best[i][1] += best_heap[i].movement/30
            results_heap_best[i][2] += best_heap[i].comparisons/30
            
            results_comb_best[i][0] += best_comb[i].duration/30
            results_comb_best[i][1] += best_comb[i].movement/30
            results_comb_best[i][2] += best_comb[i].comparisons/30
            
            results_merge_best[i][0] += best_merge[i].duration/30
            results_merge_best[i][1] += best_merge[i].movement/30
            results_merge_best[i][2] += best_merge[i].comparisons/30
        
            
        print(' - Fim do Loop')
        
        for i in range(0,3):
            del best_heap[i].vector[:]
            del best_comb[i].vector[:]
            del best_merge[i].vector[:]
    



play_best()


def printer(vec, name):

    for i in range(0, 3):
        
        if i == 0:
            order_aux = 'Decrescente'
        elif i == 1:
            order_aux = 'Crescente'
        else:
            order_aux = 'Aleatório'
        
        print('\n')
        print('Nome: '+ name)
        print('Order: '+order_aux)
        print('Len: 1.000.000')
        print('Movement: '+str(vec[i][1]))
        print('Comparisons: '+str(vec[i][2]))
        print('Tempo (s): '+str(vec[i][0]))
   



printer(results_heap_best, 'Heap Sort')
printer(results_comb_best, 'Comb Sort')
printer(results_merge_best, 'Merge Sort')





# =============================================================================
# def durations(vec):
#     d = []
#     for i in range(0, 3):
#         d.append(vec[i].duration)    
#     return d
# 
# x = [10, 100, 1000]
# =============================================================================
# =============================================================================
# 
# plt.grid(True)
# plt.title("Comparação de tempo de execução")
# 
# plt.plot( x, durations(selection), 'r^') 
# plt.plot( x, durations(selection), 'k--', color='blue', label=selection[0].name)  
# 
# plt.plot( x, durations(insertion), 'r^') 
# plt.plot( x, durations(insertion), 'k--', color='orange', label=insertion[0].name) 
# 
# plt.plot( x, durations(bubble), 'r^') 
# plt.plot( x, durations(bubble), 'k--', color='black',label=bubble[0].name) 
# 
# plt.plot( x, durations(shell), 'r^') 
# plt.plot( x, durations(shell), 'k--', color='violet', label=shell[0].name) 
# 
# plt.plot( x, durations(quick), 'r^') 
# plt.plot( x, durations(quick), 'k--', color='red', label=quick[0].name) 
# 
# plt.plot( x, durations(merge), 'r^') 
# plt.plot( x, durations(merge), 'k--', color='green', label=merge[0].name) 
# 
# plt.plot( x, durations(heap), 'r^') 
# plt.plot( x, durations(heap), 'k--', color='gray', label=heap[0].name) 
# 
# plt.plot( x, durations(comb), 'r^') 
# plt.plot( x, durations(comb), 'k--', color='yellow', label=comb[0].name) 
# 
# plt.plot( x, durations(radix), 'r^') 
# plt.plot( x, durations(radix), 'k--', color='pink', label=radix[0].name) 
# 
# plt.margins(0.05) 
# plt.xlabel("Quantidade")
# plt.ylabel("Duração (s)")
# plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
# 
# plt.show()
# 
# =============================================================================

# =============================================================================
# fig, ax = plt.subplots()
# bar_width = 0.25
# transp = 0.7
# 
# plt.figure(figsize=(10,5))
# 
# r1 = np.arange(len(durations(selection)))
# r2 = [x + bar_width for x in r1]
# r3 = [x + bar_width for x in r2]
# r4 = [x + bar_width for x in r3]
# r5 = [x + bar_width for x in r4]
# r6 = [x + bar_width for x in r5]
# r7 = [x + bar_width for x in r6]
# r8 = [x + bar_width for x in r7]
# r9 = [x + bar_width for x in r8]
# 
# plt.bar(r1, durations(selection)[0], width=bar_width, alpha=transp, color='blue', label='Selection Sort')
# 
# plt.bar(r2, durations(insertion)[0], width=bar_width, alpha=transp, color='green', label='Insertion Sort')
# plt.bar(r3, durations(bubble)[0], width=bar_width, alpha=transp, color='red', label='Bubble Sort')
# plt.bar(r4, durations(shell)[0], width=bar_width, alpha=transp, color='violet', label='Shell Sort')
# plt.bar(r5, durations(quick)[0], width=bar_width, alpha=transp, color='yellow', label='Quick Sort')
# plt.bar(r6, durations(merge)[0], width=bar_width, alpha=transp, color='pink', label='Merge Sort')
# plt.bar(r7, durations(heap)[0], width=bar_width, alpha=transp, color='gray', label='Heap Sort')
# plt.bar(r8, durations(comb)[0], width=bar_width, alpha=transp, color='orange', label='Comb Sort')
# plt.bar(r9, durations(radix)[0], width=bar_width, alpha=transp, color='black', label='Radix Sort')
# 
# 
# 
# plt.xlabel('Quantidade') 
# plt.ylabel('Duração (s)') 
# plt.title('Comparação de tempo de execução') 
# #plt.xticks([r + bar_width for r in range(len(durations(selection)))], ('10', '100', '1000')) 
# 
# plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
# plt.tight_layout() 
# plt.show()
# =============================================================================

#Teste
# =============================================================================
# create_sorting_algorithm('Descending', 10) 
# create_sorting_algorithm('Descending', 100)
# create_sorting_algorithm('Descending', 1000)
#  
# sorting(0, 3)
# 
# 
# =============================================================================





            
            
            
            
            
            
            
            
            