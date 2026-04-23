class InputMapper {
public:
    // Constructor
    InputMapper();

    // Method to map input actions to game functions
    void mapInputAction(const std::string& action, const std::string& function);

    // Method to get the mapped function for an action
    std::string getMappedFunction(const std::string& action);

    // Method to clear all mappings
    void clearMappings();

private:
    std::unordered_map<std::string, std::string> inputMappings;
};

// Implementation of InputMapper methods
InputMapper::InputMapper() {
    // Initialization logic if needed
}

void InputMapper::mapInputAction(const std::string& action, const std::string& function) {
    inputMappings[action] = function;
}

std::string InputMapper::getMappedFunction(const std::string& action) {
    return inputMappings[action]; // Return empty string if not found
}

void InputMapper::clearMappings() {
    inputMappings.clear();
}