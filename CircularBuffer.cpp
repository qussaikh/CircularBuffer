#include <iostream>
#include <array>
#include <cassert>

template <typename T, std::size_t N>
class CircularBuffer {
    static_assert(N >= 4, "Buffer size must be at least 4");

public:
    CircularBuffer() : head(0), tail(0), full(false) {}

    void clear() {
        head = tail = 0;
        full = false;
    }

    void write(const T& value) {
        buffer[head] = value;
        if (full) {
            tail = (tail + 1) % N; 
        }
        head = (head + 1) % N;
        full = (head == tail);
    }

    T read() {
        assert(!isEmpty() && "Buffer underflow: Attempt to read from an empty buffer");
        T value = buffer[tail];
        tail = (tail + 1) % N;
        full = false;
        return value;
    }

    std::size_t size() const {
        if (full) {
            return N;
        }
        if (head >= tail) {
            return head - tail;
        }
        return N - tail + head;
    }

    bool isFull() const {
        return full;
    }

    bool isEmpty() const {
        return (!full && (head == tail));
    }

    friend std::ostream& operator<<(std::ostream& os, const CircularBuffer& cb) {
        if (cb.isEmpty()) {
            os << "Buffer is empty";
        } else {
            std::size_t idx = cb.tail;
            std::size_t count = cb.size();
            for (std::size_t i = 0; i < count; ++i) {
                os << cb.buffer[idx] << " ";
                idx = (idx + 1) % N;
            }
        }
        return os;
    }

        // Compute the average of the data elements in the buffer
    template <typename U = T>
    double average() const {
        static_assert(std::is_arithmetic<U>::value, "Average can only be computed for arithmetic types.");
        assert(!isEmpty() && "Cannot compute average of an empty buffer.");

        double sum = 0.0;
        std::size_t idx = tail;
        std::size_t count = size();
        for (std::size_t i = 0; i < count; ++i) {
            sum += buffer[idx];
            idx = (idx + 1) % N;
        }
        double avg = sum / count;

        return avg;
    }

private:
    std::array<T, N> buffer;
    std::size_t head; 
    std::size_t tail; 
    bool full;       
};

void testCircularBuffer() {
  CircularBuffer<int, 5> cb;

    // Test writing and size
    cb.write(1);
    cb.write(2);
    cb.write(3);
    cb.write(4);
    assert(cb.size() == 4);
    assert(!cb.isFull());
    std::cout << "The size is: " << cb.size() << std::endl;

    // Test overwriting
    cb.write(5);
    cb.write(6);
    assert(cb.size() == 5);
    assert(cb.isFull());

    // Test average
    std::cout << "Average of buffer: " << cb.average() << std::endl;
    assert(cb.average() == (2 + 3 + 4 + 5 + 6) / 5.0);

    // Test clearing
    cb.clear();
    assert(cb.isEmpty());
    assert(cb.size() == 0);

    // Test printing
    cb.write(7);
    cb.write(8);
    cb.write(9);
    cb.write(10);
    std::cout << "Buffer contents: " << cb << std::endl;
    std::cout << "Average of buffer: " << cb.average() << std::endl;
    cb.clear();
    std::cout << "The size is: " << cb.size() << std::endl;
    std::cout << "-------------------------" << std::endl;
}

int main() {
    testCircularBuffer();
    std::cout << "All tests passed!" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    
    CircularBuffer<int, 5> cb;
    int choice = 0;

    while (choice != 7) {
        std::cout << "\nCircular Buffer Menu\n";
        std::cout << "1. Write to buffer\n";
        std::cout << "2. Read from buffer\n";
        std::cout << "3. Display buffer contents\n";
        std::cout << "4. Clear buffer\n";
        std::cout << "5. Check buffer size\n";
        std::cout << "6. Compute average\n";
        std::cout << "7. Exit\n";
        std::cout << "-------------------\n";     
        std::cout << "Enter your choice: "; 
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            std::cout << "Enter a value to write: ";
            std::cin >> value;
            cb.write(value);
            std::cout << "Value written to buffer.\n";
            break;
        }
        case 2: {
            if (cb.isEmpty()) {
                std::cout << "Buffer is empty, nothing to read.\n";
            } else {
                int value = cb.read();
                std::cout << "Value read from buffer: " << value << "\n";
            }
            break;
        }
        case 3: {
            std::cout << "Buffer contents: " << cb << "\n";
            break;
        }
        case 4: {
            cb.clear();
            std::cout << "Buffer cleared.\n";
            break;
        }
        case 5: {
            std::cout << "Buffer size: " << cb.size() << "\n";
            break;
        }
        case 6:
        if (cb.isEmpty()) {
                std::cout << "Buffer is empty, cannot compute average.\n";
            } else {
                std::cout << "Average of buffer: " << cb.average() << "\n";
            }
            break;
        case 7:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
