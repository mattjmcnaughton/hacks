const PUSH = "push";
const ADD = "add";
const MINUS = "minus";

let virtualMachine = function(program) {
  let programCounter = 0;
  let stack = [];
  let stackPointer = 0;

  while (programCounter < program.length) {
    // fetch
    let currentInstruction = program[programCounter];

    // decode
    switch (currentInstruction) {
      // execute
      case PUSH:
        stack[stackPointer] = program[programCounter + 1];
        stackPointer++;
        programCounter++;
        break;

      case ADD:
        right = stack[stackPointer-1];
        stackPointer--;
        left = stack[stackPointer-1];
        stackPointer--;

        stack[stackPointer] = left + right;
        stackPointer++;
        break;

      case MINUS:
        right = stack[stackPointer-1];
        stackPointer--;
        left = stack[stackPointer-1];
        stackPointer--;

        stack[stackPointer] = left - right;
        stackPointer++;
        break;
    }

    programCounter++;
  }

  console.log("stacktop: ", stack[stackPointer-1]);
}

let program = [
  PUSH, 3,
  PUSH, 4
  ADD,
  PUSH, 5,
  MINUS
];

virtualMachine(program);
