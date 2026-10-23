cmake_minimum_required(VERSION 3.16)
project(Taller_2_Estructura_de_datos_prueba)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Taller_2_Estructura_de_datos_prueba main.cpp
        Data_structures/Data_structures_h/Node.hpp
      
        Data_structures/Data_structures_h/Queue.hpp

        Data_structures/Data_structures_h/Stack.hpp

        Clases/Clases_h/Persona.hpp
        Clases/Clases_cpp/Persona.cpp
        Clases/Clases_h/Paciente.hpp
        Clases/Clases_h/Servicio.hpp
        Clases/Clases_h/Atencion.hpp
        Clases/Clases_cpp/Atencion.cpp
        Clases/Clases_cpp/Paciente.cpp
        Clases/Clases_cpp/Servicio.cpp
        Data_structures/Data_structures_h/NodoAVL.hpp
        Data_structures/Data_structures_cpp/NodoAVL.cpp
        Data_structures/Data_structures_h/AVL.hpp
        Data_structures/Data_structures_cpp/AVL.cpp
        Data_structures/Data_structures_h/NodoDecision.hpp
        Data_structures/Data_structures_cpp/NodoDecision.cpp
        Data_structures/Data_structures_h/ArbolDecision.hpp
        Data_structures/Data_structures_cpp/ArbolDecision.cpp
        Data_structures/Data_structures_h/List.hpp

        Core/Core_h/CargarArchivo.hpp
        Core/Core_cpp/CargarArchivo.cpp
        Core/Core_h/SistemaHospital.hpp
        Core/Core_cpp/SistemaHospital.cpp
        Core/Core_h/Menu.hpp
        Core/Core_cpp/Menu.cpp
)
