# Cryptography Journey

This repository documents my journey through **mathematical cryptography**, with a strong emphasis on understanding cryptographic systems **from first principles**.

Rather than relying on black-box libraries, the goal of this project is to bridge the gap between **mathematical definitions**, **algorithms**, and **concrete implementations**, primarily using **C++**. Each component is approached as both a mathematical object and an engineering artifact.

This repository is intentionally focused on **depth over breadth**.

---

## Motivation

Modern cryptographic systems—especially those used in **blockchains** and **zero-knowledge proofs**—are built on layers of algebra, number theory, and carefully designed algorithms. While high-level frameworks and DSLs make these systems accessible, they often hide the underlying structure that determines correctness, security, and performance.

My motivation for this repository is to:

- Develop a **deep, internal understanding** of cryptographic primitives
- Learn how mathematical abstractions map to real algorithms and code
- Build intuition for **why cryptographic systems work**, not just how to use them
- Prepare for advanced areas such as **zero-knowledge proofs**, **verifiable computation**, and **protocol design**

This work is inspired by studying texts such as *Introduction to Mathematical Cryptography* and zero-knowledge–focused literature, and by re-implementing the ideas they present.

---

## Philosophy

This repository follows a few core principles:

### 1. First Principles
Algorithms are implemented starting from their mathematical definitions. Whenever possible, derivations and invariants are understood before code is written.

### 2. Correctness Before Optimization
Clarity and correctness take priority over performance. Optimizations are explored only after the underlying ideas are fully understood.

### 3. Explicit Invariants
Many implementations are written in a way that mirrors mathematical proofs, preserving explicit invariants rather than relying on clever tricks.

### 4. Learning-Oriented Code
The code is not intended to be production-ready. Instead, it is written to be:
- readable
- auditable
- easy to reason about

---

## Scope

The repository explores foundational topics in cryptography, including (but not limited to):

- Number theory and modular arithmetic
- The Euclidean and extended Euclidean algorithms
- Modular inverses and finite field arithmetic
- Big integer arithmetic (from scratch)
- Polynomial arithmetic and interpolation
- Cryptographic hash constructions
- Merkle trees and authenticated data structures
- Elliptic curve arithmetic
- Foundations relevant to zero-knowledge proofs (R1CS, polynomial representations, etc.)

As the project evolves, it will increasingly focus on primitives and constructions relevant to:
- zero-knowledge proof systems
- blockchain protocols
- verifiable computation

---

## Structure

A typical structure of the repository looks like:

