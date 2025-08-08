# 📌 Multilevel Queue Transaction Scheduler

A **C-based simulation** of **Multilevel Queue Scheduling** for banking transactions, implementing multiple CPU scheduling algorithms to efficiently manage high-, medium-, and low-priority tasks.

This project was developed as part of the **Operating System Laboratory (CSC23CL206)** course for **B.Tech in Artificial Intelligence and Machine Learning**.

---

## 📖 Overview

The scheduler organizes and executes transactions based on priority:

| Priority Level | Transaction Types | Scheduling Algorithm |
|----------------|------------------|----------------------|
| **High (1)**   | Cash Withdrawal, Fund Transfer | Round Robin (RR) — Time Quantum = 2 |
| **Medium (2)** | Bill Payment, Balance Check   | First-Come, First-Served (FCFS) |
| **Low (3)**    | Loan Processing, Account Creation | Shortest Job First (SJF) |

This approach ensures:
- Urgent transactions are processed quickly.
- Medium-priority tasks are handled fairly.
- Low-priority, long-running tasks are optimized for efficiency.

---

## 🎯 Objectives

- **Efficient Transaction Prioritization** — categorize and process tasks according to urgency.
- **Algorithm Implementation** — integrate RR, FCFS, and SJF scheduling strategies.
- **Dynamic Queue Assignment** — assign tasks to queues based on user input.
- **Performance Visualization** — display Gantt Chart and transaction details.
- **Metrics Analysis** — calculate Turnaround Time (TAT) and Waiting Time (WT).

---

## 🛠 Technologies Used

- **Language:** C
- **Core Concepts:** CPU Scheduling (RR, FCFS, SJF), Multilevel Queues
- **Libraries:**  
  - `stdio.h` – input/output functions  
  - `stdlib.h` – memory allocation and process control  
  - `string.h` – string manipulation  
  - `unistd.h` – process delays for simulation

---

🧮 Sample Input:

Do you want all transactions to have the same priority level? (1 = Yes, 0 = No): 0
Enter number of transactions: 3

Enter priority (1-High, 2-Medium, 3-Low) for transaction 1: 1
Enter processing time and arrival time for transaction 1: 4 0

Enter priority (1-High, 2-Medium, 3-Low) for transaction 2: 2
Enter processing time and arrival time for transaction 2: 3 1

Enter priority (1-High, 2-Medium, 3-Low) for transaction 3: 3
Enter processing time and arrival time for transaction 3: 2 2

---

📊 Expected Output: 

Gantt Chart — execution timeline of transactions

Transaction Table — includes:

Arrival Time (AT)

Processing Time (PT)

Completion Time (CT)

Turnaround Time (TAT)

Waiting Time (WT)

Transaction Type

Performance Metrics — average TAT & WT

---

## 🚀 How to Compile & Run

You can run this program in **two ways**:

---

### 1️⃣ On Your Local Machine (Using GCC)

**Compile:**
```bash
gcc main.c -o scheduler
