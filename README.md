# 📊 Personal Health Metrics Tracker (DSA Mini Project)

A console-based **Personal Health Metrics Tracker** built in **C language** using the **Doubly Linked List** data structure. This project stores daily health metrics such as **steps, calories burned, and sleep hours**, and provides features to analyze and visualize this data.

---

## 📝 Introduction

The project demonstrates how Data Structures (specifically **Doubly Linked Lists**) can be used to efficiently store and manage daily health-related records.  
Users can input new health data, view historical records, analyze trends through summaries, and visualize step counts using an ASCII bar chart.

The project also helps practice:
- Dynamic memory allocation  
- Struct-based data grouping  
- List traversal  
- Menu-driven program design  

---

## 🚀 Features

- Add new daily health records  
- View all historical records in a clean table format  
- Summary statistics:
  - Total steps, calories burned, sleep hours  
  - Averages  
  - Best and worst step-count days  
- ASCII bar chart visualization of daily step counts  
- Automatic date suggestion for convenience  
- Memory cleanup before exiting  

---

## 🧠 Data Structures Used

### **1. Structure (struct)**  
Used to group related data (date, steps, calories, sleep hours) into a single entity.

### **2. Doubly Linked List**  
Used to store multiple records. Supports:
- Sequential traversal  
- Easy insertion at the end  
- Memory efficiency  
- Bidirectional movement via `prev` and `next`  

---

## 🛠️ Functions Used (with Purpose)

### **createNode()**  
Creates a new doubly linked list node and allocates memory.

### **insertRecord()**  
Adds a new record at the end of the linked list.

### **addNewRecord()**  
Inputs user data and inserts it into the list.

### **displayRecords()**  
Shows all stored records in a formatted table.

### **calculateSummary()**  
Calculates totals, averages, min, and max values from the data.

### **visualizeSteps()**  
Creates a text-based bar chart to visualize steps.

### **cleanup()**  
Frees all dynamically allocated nodes before the program exits.

---

## ▶️ How to Run This Project

### **1. Install GCC Compiler (MinGW-w64 on Windows)**  
Verify installation:
gcc --version

### **2. Compile the Program**
gcc health_tracker.c -o health

### **3. Run the Program (PowerShell)**
.\health.exe

### **4. Interact through menu options**  
Follow the simple menu system to use all features.

---

## 🎯 Learning Outcomes

By completing this project, you will learn:

- Implementation of **Doubly Linked Lists** in C  
- Use of **structures** to store grouped data  
- Dynamic memory handling using `malloc` and `free`  
- Menu-driven program development  
- List traversal and node insertion  
- Computing summary statistics  
- Creating simple data visualizations in terminal  
- Clean, modular C programming practices  

---

## 📌 Ideal For

- DSA Mini Project submissions  
- Students learning C + Linked Lists  
- Beginners practicing struct + pointer concepts  
- Anyone who wants a real-life application using DSA concepts  

---

## 👨‍💻 Author  
**Your Name (Update before uploading)**  
BCA Student • DSA Mini Project  

Feel free to extend this project, add file handling, sorting, or more visualizations!
