# Smart Campus Energy & Facility Management System

An integrated, multi-file console-based C application engineered to solve operational optimization and sustainability challenges on a modern university campus. The system seamlessly handles macro-level building analytics, automated micro-room climate management, cross-functional maintenance ticketing workflows, smart network hardware asset lifecycles, and cryptographic user security administration access controls.

The architecture is designed as a modular, distributed codebase where five distinct modules interact dynamically over a central header runtime matrix.

## Structural Architecture & File Blueprint

The application is structured across six distinct files to clearly isolate individual contribution boundaries while preserving global systemic operations:

* **`common.h`**: The central bridge of the application. It consolidates all system-wide dimension constants (`MAX_ROOMS`, `MAX_USERS`, etc.), houses shared composite types, defines nested date sub-structures, and registers common operational function signatures.
* **`member1.c` (Building Analytics)**: Manages structures tracking physical floors, baseline electrical utilities, and water volumes. Features an automated efficiency algorithm to dynamically compute structure eco-ratings.
* **`member2.c` (Eco Smart-Room Dashboard)**: Manages localized room spaces, occupancy limits, and temperature thresholds. Automatically targets environmental energy waste and passes active emergency variables to the maintenance queue.
* **`member3.c` (Facility Maintenance Tickets)**: Orchestrates the campus repair pipeline. Cross-references security profile lists to deploy personnel and checks serial signatures to restore repaired hardware components.
* **`member4.c` (Embedded Hardware Registry)**: Maintains an online log tracking edge IoT devices using nested date structures. Automatically files unresolved service orders if devices trigger analytical fault indicators.
* **`member5.c` (Identity System & Core Runner)**: Orchestrates the overall execution loop. Implements symmetric bitwise cryptographic routines to secure passwords in running blocks and updates global session tokens to protect restricted administrative actions across external files.

## Architecture Design & Specification Constraints

This system is engineered under strict structural design patterns to showcase modular programming competencies, clean code isolation, and team-based distributed development:

1. **Decoupled Architecture**: Divided into 5 distinct domain modules containing a dedicated component structure and exactly 5 specialized, high-cohesion functions to enforce strict separation of concerns.
2. **Multi-File Scope Linking**: Implements isolated source compilation units connected via a central configuration matrix utilizing `extern` storage tokens to eliminate global scope pollution.
3. **Pass-by-Reference Memory Optimization**: Utilizes memory address pointers and structural arrow (`->`) notation across cross-module boundaries to mutate datasets directly, keeping the application memory footprint minimal.
4. **Nested Structural Typology**: Implements composite design paradigms by nesting sub-structures (such as custom `Date` layers) inside parent state models to maintain relational data integrity.
5. **Cross-Module Pipelines**: Features logical event-driven inter-connectivity between decoupled files, enabling automated cascading workflows (e.g., telemetry failures in one module dynamically registering tracking entries in another).
6. **Bitwise Cryptographic Obscurity**: Features standard symmetric XOR bitwise routines to obscure plaintext credentials in active memory blocks to demonstrate a fundamental data abstraction layer.
7. **Algorithmic Search & Data Indexing**: Integrates structural bubble-sort implementations to re-index operational entities alongside advanced string-handling matrices (`strstr`, `strcmp`) for real-time asset tracking.
8. 
## Compilation and Execution

To compile and link all six components into a unified executable file using the GCC compiler, navigate to the source directory and run the following terminal command:

```bash
gcc member5.c member1.c member2.c member3.c member4.c -o smart_campus
