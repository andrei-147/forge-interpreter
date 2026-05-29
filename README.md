# Forge Interpreter

Forge Interpreter is the official runtime for **ForgeScript (`.mold`)**, a lightweight template-driven language designed for rapid project scaffolding, automation, and environment generation.

## What is Forge?
Forge (short for _*F*ramework for *O*rganized and *R*apid *G*eneration of *E*nvironments_) is a cross-platform, free and open source CLI project management tool.

_More details over on [FORGE](https://github.com/andrei-147/forge)!_

## What is ForgeScript?

ForgeScript is a declarative language used to define reusable project templates called **molds**. Each `.mold` file describes how a project should be initialized and which actions can be executed through the Forge CLI.

Forge is built around a simple idea:

> Define once, generate and reuse everywhere.

## Core Concepts

### Templates

A template defines a project type (e.g. `cpp`, `node`, `python`) and lives in the global template directory.

```forge
template "cpp"
```

### Properties

Static configuration values used across the template.

```forge
properties {
    property1 = 0
    property2 = 1
}
```

### Tasks

Tasks are executable command groups exposed to the CLI.

```forge
task init() {
    mkdir "project"
    cd "project"
}
```

Tasks may accept parameters, including typed values and CLI flags.

### CLI Flags (Opt)

Forge supports optional CLI-style parameters inside tasks.

```forge
task init(
    git: Opt("g", "git")
) {
    if git {
        exec "git init"
    }
}
```

## Installation

Forge Interpreter is currently in early development.

```bash
git clone https://github.com/andrei-147/forge-interpreter
cd forge-interpreter
```

Build instructions will depend on the final implementation language (C++ target planned).

## Usage

### Initialize a project

```bash
forge init cpp my_project
```

This:

* Loads `cpp.mold` from the template directory
* Executes the `init` task
* Generates a `.forge` project configuration file

### Run a task

```bash
forge run init
```

Forge:

* Reads `.forge`
* Resolves the template
* Executes the matching task

## Project State (.forge)

Each project stores metadata in a `.forge` file:

```json
{
  "template": "cpp",
  "args": {
    "name": "my_project"
  }
}
```

This allows Forge to operate without re-specifying the template after initialization.

## Language Pipeline

Forge Interpreter follows a classic compiler architecture:

1. **Lexer** – converts source code into tokens
2. **Parser** – builds an abstract syntax tree (AST)
3. **Interpreter** – executes tasks and commands

## Supported Commands (Initial Set)

### IO

* `print`
* `pinfo`
* `pwarn`
* `perr`

### Console / System

* `cd`
* `cp`
* `rm`
* `mkdir`
* `rmdir`
* `mv`
* `touch`
* `ls`
* `exec`

## Design Goals

Forge is designed to be:

* Simple to read and write
* Predictable and deterministic
* Extensible through templates
* CLI-first and automation-focused

## Status

Forge Interpreter is currently:

* 🔧 In design / early implementation phase
* 🧪 Not production-ready
* 🚧 Syntax and standard library subject to change

## License

This project is licensed under the terms of the [LICENSE](LICENSE) file.

## Vision

Forge aims to become a universal scaffolding system where project setup logic is portable, reusable, and shareable through `.mold` templates.
