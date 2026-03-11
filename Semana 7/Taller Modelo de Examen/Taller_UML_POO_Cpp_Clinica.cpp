#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>

using namespace std;

// Excepción personalizada
class EntidadNoEncontrada : public exception {
public:
    string msg;
    EntidadNoEncontrada(string m) : msg(m) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

// ========== CLASE PERSONA ==========
class Persona {
protected:
    string nombre;
public:
    Persona(string n) : nombre(n) {}
    virtual void mostrar() = 0;
    string getNombre() { return nombre; }
    virtual ~Persona() {}
};

// ========== CLASES PARA COMPOSICIÓN ==========
class EntradaHistoria {
public:
    string fecha;
    string diagnostico;
    
    EntradaHistoria(string f, string d) : fecha(f), diagnostico(d) {}
};

class HistoriaClinica {
public:
    vector<EntradaHistoria> entradas;
    
    void agregarEntrada(string fecha, string diag) {
        entradas.push_back(EntradaHistoria(fecha, diag));
    }
    
    void mostrar() {
        cout << "--- HISTORIAL MEDICO ---" << endl;
        for(auto& e : entradas) {
            cout << "  " << e.fecha << ": " << e.diagnostico << endl;
        }
    }
};

// ========== CLASES DERIVADAS ==========
class Paciente : public Persona {
public:
    string dni;
    int edad;
    string telefono;
    HistoriaClinica historia;  // COMPOSICIÓN
    
    Paciente(string n, string d, int e, string t) : Persona(n) {
        if(d.length() != 8) 
            throw invalid_argument("DNI debe tener 8 digitos");
        if(e < 0 || e > 120)
            throw invalid_argument("Edad invalida");
        if(t.length() != 9)
            throw invalid_argument("Telefono debe tener 9 digitos");
            
        dni = d;
        edad = e;
        telefono = t;
    }
    
    void mostrar() override {
        cout << "Paciente: " << nombre << " - DNI: " << dni << endl;
    }
};

class Doctor : public Persona {
public:
    int codigo;
    string especialidad;
    double tarifa;
    
    Doctor(int c, string n, string e, double t) : Persona(n) {
        if(t <= 0)
            throw invalid_argument("Tarifa debe ser mayor a 0");
        if(c <= 0)
            throw invalid_argument("Codigo invalido");
            
        codigo = c;
        especialidad = e;
        tarifa = t;
    }
    
    void mostrar() override {
        cout << "Doctor: " << nombre << " - " << especialidad << endl;
    }
};

// ========== CLASE CITA ==========
class Cita {
public:
    int id;
    Paciente* paciente;  // Puntero observador
    Doctor* doctor;      // Puntero observador
    string fecha;
    string hora;
    string motivo;
    bool activa;
    
    Cita(int i, Paciente* p, Doctor* d, string f, string h, string m) {
        // Validación simple de fecha
        if(f.length() != 10 || f[4] != '-' || f[7] != '-')
            throw invalid_argument("Formato fecha debe ser YYYY-MM-DD");
        
        // Validación simple de hora
        if(h.length() != 5 || h[2] != ':')
            throw invalid_argument("Formato hora debe ser HH:MM");
            
        id = i;
        paciente = p;
        doctor = d;
        fecha = f;
        hora = h;
        motivo = m;
        activa = true;
    }
    
    void mostrar() {
        if(activa) {
            cout << "Cita #" << id << " | " << fecha << " " << hora 
                 << " | Dr: " << doctor->getNombre() << endl;
        }
    }
    
    void cancelar() { activa = false; }
};

// ========== CLASE CLINICA ==========
class Clinica {
public:
    vector<unique_ptr<Paciente>> pacientes;  // Smart pointers
    vector<unique_ptr<Doctor>> doctores;     // Smart pointers
    vector<unique_ptr<Cita>> citas;          // Smart pointers
    int contadorCitas;
    
    Clinica() : contadorCitas(1) {}
    
    void registrarPaciente(string n, string d, int e, string t) {
        auto p = make_unique<Paciente>(n, d, e, t);
        pacientes.push_back(move(p));
    }
    
    void registrarDoctor(int c, string n, string e, double t) {
        auto d = make_unique<Doctor>(c, n, e, t);
        doctores.push_back(move(d));
    }
    
    Paciente* buscarPaciente(string dni) {
        for(auto& p : pacientes) {
            if(p->dni == dni) return p.get();
        }
        throw EntidadNoEncontrada("Paciente no encontrado");
    }
    
    Doctor* buscarDoctor(int cod) {
        for(auto& d : doctores) {
            if(d->codigo == cod) return d.get();
        }
        throw EntidadNoEncontrada("Doctor no encontrado");
    }
    
    void agendarCita(string dniPac, int codDoc, string fecha, string hora, string motivo) {
        Paciente* p = buscarPaciente(dniPac);
        Doctor* d = buscarDoctor(codDoc);
        
        // Validar cita duplicada
        for(auto& c : citas) {
            if(c->activa && c->doctor == d && c->fecha == fecha && c->hora == hora) {
                throw runtime_error("Ya existe una cita en ese horario");
            }
        }
        
        auto c = make_unique<Cita>(contadorCitas++, p, d, fecha, hora, motivo);
        citas.push_back(move(c));
        cout << "Cita agendada con exito" << endl;
    }
    
    void cancelarCita(int id) {
        for(auto& c : citas) {
            if(c->id == id && c->activa) {
                c->cancelar();
                cout << "Cita cancelada" << endl;
                return;
            }
        }
        throw EntidadNoEncontrada("Cita no encontrada");
    }
    
    void listarCitasPaciente(string dni) {
        Paciente* p = buscarPaciente(dni);
        cout << "\nCitas de " << p->getNombre() << ":" << endl;
        for(auto& c : citas) {
            if(c->activa && c->paciente == p) {
                c->mostrar();
            }
        }
    }
    
    void listarCitasDoctor(int cod) {
        Doctor* d = buscarDoctor(cod);
        cout << "\nCitas del Dr. " << d->getNombre() << ":" << endl;
        for(auto& c : citas) {
            if(c->activa && c->doctor == d) {
                c->mostrar();
            }
        }
    }
    
    void agregarDiagnostico(string dni, string fecha, string diag) {
        Paciente* p = buscarPaciente(dni);
        p->historia.agregarEntrada(fecha, diag);
        cout << "Diagnostico agregado" << endl;
    }
    
    void verHistorial(string dni) {
        Paciente* p = buscarPaciente(dni);
        p->historia.mostrar();
    }
};

// ========== CLASE REPORTE (DEPENDENCIA) ==========
class Reporte {
public:
    static void porEspecialidad(Clinica& c) {
        cout << "\n=== REPORTE POR ESPECIALIDAD ===" << endl;
        
        // Contador manual
        int cardio = 0, pedia = 0, derma = 0, otros = 0;
        
        for(auto& cita : c.citas) {
            if(cita->activa) {
                string esp = cita->doctor->especialidad;
                if(esp == "Cardiologia") cardio++;
                else if(esp == "Pediatria") pedia++;
                else if(esp == "Dermatologia") derma++;
                else otros++;
            }
        }
        
        cout << "Cardiologia: " << cardio << endl;
        cout << "Pediatria: " << pedia << endl;
        cout << "Dermatologia: " << derma << endl;
        cout << "Otras: " << otros << endl;
    }
};

// ========== MAIN ==========
int main() {
    Clinica clinica;
    int opcion = 0;
    
    // Algunos datos de ejemplo
    try {
        clinica.registrarDoctor(101, "Ana Lopez", "Cardiologia", 150);
        clinica.registrarDoctor(102, "Carlos Ruiz", "Pediatria", 120);
        clinica.registrarPaciente("Juan Perez", "12345678", 30, "987654321");
        clinica.registrarPaciente("Maria Gomez", "87654321", 25, "123456789");
    } catch(...) {}
    
    do {
        try {
            cout << "\n===== CLINICA SALUD+ =====" << endl;
            cout << "1. Registrar paciente" << endl;
            cout << "2. Registrar doctor" << endl;
            cout << "3. Agendar cita" << endl;
            cout << "4. Cancelar cita" << endl;
            cout << "5. Listar citas x paciente" << endl;
            cout << "6. Listar citas x doctor" << endl;
            cout << "7. Agregar diagnostico" << endl;
            cout << "8. Ver historial medico" << endl;
            cout << "9. Reporte x especialidad" << endl;
            cout << "10. Salir" << endl;
            cout << "Opcion: ";
            cin >> opcion;
            
            if(opcion < 1 || opcion > 10) {
                throw out_of_range("Opcion invalida");
            }
            
            if(opcion == 1) {
                string nom, dni, tel;
                int edad;
                cout << "Nombre: "; cin >> nom;
                cout << "DNI: "; cin >> dni;
                cout << "Edad: "; cin >> edad;
                cout << "Telefono: "; cin >> tel;
                
                clinica.registrarPaciente(nom, dni, edad, tel);
                cout << "Paciente registrado" << endl;
            }
            else if(opcion == 2) {
                int cod;
                string nom, esp;
                double tar;
                cout << "Codigo: "; cin >> cod;
                cout << "Nombre: "; cin >> nom;
                cout << "Especialidad: "; cin >> esp;
                cout << "Tarifa: "; cin >> tar;
                
                clinica.registrarDoctor(cod, nom, esp, tar);
                cout << "Doctor registrado" << endl;
            }
            else if(opcion == 3) {
                string dni, fecha, hora, motivo;
                int cod;
                cout << "DNI paciente: "; cin >> dni;
                cout << "Codigo doctor: "; cin >> cod;
                cout << "Fecha (YYYY-MM-DD): "; cin >> fecha;
                cout << "Hora (HH:MM): "; cin >> hora;
                cout << "Motivo: "; cin >> motivo;
                
                clinica.agendarCita(dni, cod, fecha, hora, motivo);
            }
            else if(opcion == 4) {
                int id;
                cout << "ID cita: "; cin >> id;
                clinica.cancelarCita(id);
            }
            else if(opcion == 5) {
                string dni;
                cout << "DNI paciente: "; cin >> dni;
                clinica.listarCitasPaciente(dni);
            }
            else if(opcion == 6) {
                int cod;
                cout << "Codigo doctor: "; cin >> cod;
                clinica.listarCitasDoctor(cod);
            }
            else if(opcion == 7) {
                string dni, fecha, diag;
                cout << "DNI paciente: "; cin >> dni;
                cout << "Fecha: "; cin >> fecha;
                cout << "Diagnostico: "; cin >> diag;
                clinica.agregarDiagnostico(dni, fecha, diag);
            }
            else if(opcion == 8) {
                string dni;
                cout << "DNI paciente: "; cin >> dni;
                clinica.verHistorial(dni);
            }
            else if(opcion == 9) {
                Reporte::porEspecialidad(clinica);
            }
            
        }
        catch(EntidadNoEncontrada& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch(invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch(out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch(runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch(...) {
            cout << "Error desconocido" << endl;
        }
        
    } while(opcion != 10);
    
    cout << "Gracias por usar el sistema" << endl;
    return 0;
}