# MyKhaata – Personal Financial Management System (C++)

**MyKhaata** is a console-based C++ application designed to manage personal finances through a structured and user-friendly system. Developed using object-oriented programming principles, the application provides functionality for managing users, accounts, and financial transactions efficiently.

---

## 🧾 Project Overview

This project was developed as part of the Object-Oriented Programming (OOP) course at **Air University**. The system simulates basic features of a personal finance manager, including user account handling, transaction recording, and financial insights based on categories and time periods.

---

## ✨ Key Features

- **Admin and User Login System**
- **User Registration with Validation**
- **Account Creation and Management**
- **Add / View / Edit / Delete Transactions**
- **Transaction Filtering by Date and Category**
- **File-Based Data Persistence**
- **Basic Financial Insights**

---

## 🛠 Technologies Used

| Technology | Purpose                      |
|------------|------------------------------|
| C++        | Core programming language     |
| OOP        | Application architecture      |
| File I/O   | Data persistence (no database)|
| Console UI | User interface                |

---

## 🧠 OOP Concepts Implemented

- **Abstract Classes** – Common interface for user types (`Person`)
- **Inheritance** – Derived classes for `User` and `Admin`
- **Polymorphism** – Virtual functions for dynamic behavior
- **Encapsulation** – Structured and secure class design
- **Modularity** – Separation of concerns across classes

---

### Prerequisites
- C++ compiler (e.g., `g++`, `clang`)
- Terminal or command prompt

### Steps to Run

```bash
git clone https://github.com/yourusername/mykhaata-cpp.git
cd mykhaata-cpp
g++ main.cpp -o mykhaata
./mykhaata
