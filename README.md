# Firewall-Simulation

#### Description
The **Firewall-Simulation** implements a firewall application capable of filtering internet packets based on a predefined set of rules. Developed in C++ for the core functionality and Bash for parsing and feeding rules into the system, this project showcases my ability to handle network-level packet filtering and efficient memory management. The firewall focuses on correctness, memory safety, and performance, as packet filtering is done based on source/destination IP addresses and ports. This project also emphasizes efficient handling of memory and real-time performance tracking, demonstrating my skills in system-level programming and optimization.

#### Technologies Used
- **Programming Languages**: C++, Bash
- **Libraries/Frameworks**: Standard C++ libraries for string and memory management, dynamic library handling
- **Tools**: Git for version control, Makefile for build automation

#### Features
- **Packet Filtering**: Filters incoming and outgoing packets based on source/destination IP address and port, with support for subnet masks and port ranges.
- **Memory Safety**: Focused on preventing memory leaks through the correct use of C++'s automatic memory management and destructor handling.
- **Performance Tracking**: Measures and outputs runtime performance to ensure efficient packet filtering.
- **Flexible Rule Parsing**: Supports dynamic parsing of rules through Bash scripts, making it easy to update and apply new rules in real-time.
- **Dynamic Libraries**: Implements key functionalities in dynamic libraries to enable modular design and reusability of core firewall components.
  
#### Getting Started
##### Prerequisites
- C++ compiler (e.g., g++)
- Bash (for rule parsing)
  
##### Installation
1. Clone the repository to your local machine:
    ```bash
    git clone https://github.com/[YourGitHubUsername]/Firewall-Simulation.git
    cd Firewall-Simulation
    ```
2. Compile the project:
    ```bash
    make
    ```

##### Usage
1. Define your packet filtering rules in a text file (e.g., `rules.txt`), specifying fields like `src-ip`, `dst-ip`, `src-port`, and `dst-port`:
    ```bash
    src-ip=122.0.0.0/8
    dst-port=22-22
    ```

2. Run the firewall with packet inputs:
    ```bash
    cat packets.txt | ./firewall.exe "src-ip=122.0.0.0/8"
    ```

#### Contributing
Contributions to the **Firewall-Simulation** project are welcome! Feel free to fork the repository, make your changes, and submit a pull request with your improvements.
