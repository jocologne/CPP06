#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main() {
    Data* data = new Data;
    data->value = 42;
    data->name = "Test Data";
    
    std::cout << "Original pointer: " << data << std::endl;
    std::cout << "Original value: " << data->value << std::endl;
    std::cout << "Original name: " << data->name << std::endl;
    
    // Serializar
    unsigned long serialized = Serializer::serialize(data);
    std::cout << "Serialized value: " << serialized << std::endl;
    
    // Desserializar
    Data* deserialized = Serializer::deserialize(serialized);
    std::cout << "Deserialized pointer: " << deserialized << std::endl;
    std::cout << "Deserialized value: " << deserialized->value << std::endl;
    std::cout << "Deserialized name: " << deserialized->name << std::endl;
    
    // Verificação - AGORA USANDO a variável deserialized
    if (data == deserialized) {
        std::cout << "✓ SUCCESS: Pointers match!" << std::endl;
    } else {
        std::cout << "✗ FAIL: Pointers don't match!" << std::endl;
        return 1;
    }
    
    delete data;
    return 0;
}