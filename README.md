# CircularBuffer Project 

This project implements a generic **Circular Buffer** template class in C++ that supports efficient and safe storage and retrieval of data in a circular (ring) buffer.

## features 

- **Write**: Add elements to the buffer, overwriting the oldest elements if the buffer is full.
- **Read**: Retrieve elements from the buffer in FIFO order, with protection against underflow.
- **Clear**: Reset the buffer to its initial empty state.
- **Average**: Compute the average of numerical elements in the buffer.
- **Dynamic Size Management**: Check buffer size, and states (full/empty).
- **Menu-Driven Interface**: Interactive console menu for testing and using the buffer.


### Compilation

1. Save the provided code to a file named `CircularBuffer.cpp`.
2. Compile the program using a C++ compiler. For example:

   ```bash
   g++ CircularBuffer.cpp -o CircularBuffer
   ```

3. Run the program:

   ```bash
   ./CircularBuffer
   ```

   ## Testing

The program includes a `testCircularBuffer` function to verify the correctness of core operations such as writing, reading, clearing, and computing averages. The test results are printed to the console.

To run the tests, simply execute the program. Test results are displayed before the menu interface.


Enjoy using the Circular Buffer project! 🎉

