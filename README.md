# JIT Expression Evaluator

A lightweight Just-In-Time (JIT) compiler in **C** that parses and evaluates mathematical expressions by dynamically generating, compiling, and executing code at runtime.

## 🚀 Features
- Parses arithmetic expressions (`+`, `-`, `*`, `/`) into a DAG (Directed Acyclic Graph).
- Generates C code on the fly to evaluate the parsed expression.
- Dynamically compiles and runs the code for optimized performance.
- Includes custom operations like `sigmoid` for extended functionality.
- Built with a clean modular design: **lexer**, **parser**, **JIT compiler**, and **system utilities**.

---

## 🛠️ Tech Stack
- **Language:** C
- **Build Tool:** Makefile
- **Core Components:**
  - `lexer.c` – Tokenizes the input.
  - `parser.c` – Builds the expression DAG.
  - `jitc.c` – Generates and compiles C code dynamically.
  - `system.c` – Handles runtime loading and execution.

---

## ⚙️ Build & Run
1. **Compile the project:**
   ```bash
   make
