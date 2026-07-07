# Advanced Bank System & ATM Console Application

## Overview
This project is a robust, object-oriented C++ console application that simulates a complete banking environment. It is divided into two main subsystems that operate within the same ecosystem:
1. **Advanced Bank System (Staff App):** A comprehensive management system for bank employees to manage clients, users, transactions, and currency exchanges.
2. **ATM System (Client App):** A realistic ATM interface for bank clients to securely check balances, deposit, and withdraw funds.

Both systems seamlessly share a centralized, flat-file database architecture ensuring real-time data consistency.

## Core Features
### 🏦 Bank Management System
* **Client Management:** Add, update, delete, find, and list bank clients.
* **Transaction Engine:** Handle deposits, withdrawals, and inter-account transfers.
* **User & Permissions Management:** Admin-level control to manage bank employees with strict role-based access control (RBAC).
* **Currency Exchange:** Real-time currency calculator and rate updater.
* **Login Register Log:** Tracks and logs all staff logins with timestamps.

### 🏧 ATM System
* **Client Authentication:** Secure login using Account Number and PIN.
* **Quick & Normal Withdrawals:** Flexible withdrawal systems with strict balance validation.
* **Deposits:** Instant account deposits.
* **Real-time Synchronization:** All ATM transactions instantly reflect in the main bank system database.

## Technical Architecture
* **Language:** C++
* **Paradigm:** Object-Oriented Programming (OOP)
* **Data Storage:** Flat-file database (`.txt` files)
* **Design:** Highly modular design utilizing static utility classes, template-based input validation, and inheritance-based UI rendering.

## Future Features / Roadmap
The following features are planned for future updates to make the system even more enterprise-ready:
* **🔒 Encrypted Client PINs:** Enhance security by encrypting client PINs in the database (similar to staff passwords).
* **🧾 ATM PIN Change:** Allow clients to update their PIN directly from the ATM interface.
* **💱 Cross-Currency Transfers:** Automatically convert and transfer funds between accounts using different base currencies.
* **📜 Global Transaction Log:** A comprehensive, admin-viewable audit log for all deposits, withdrawals, and transfers across the system.
* **⛔ Fraud Prevention (Account Lockout):** Automatically lock ATM accounts after 3 failed PIN attempts, requiring bank staff to unlock them.
