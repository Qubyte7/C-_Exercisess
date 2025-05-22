Student student1("innocent",18,"y3b");  // Stack allocation

Created on the stack
Automatically deallocated when out of scope
Limited by stack size
Faster allocation

Student *student4 = new Student("dan",17,"y3a");  // Heap allocation

Created on the heap using new
Must be manually deallocated using delete
Limited by system memory
Slower allocation