#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;

// Classe base abstrata KPI
class KPI {
public:
    virtual double calcular() const = 0; // método virtual puro
    virtual ~KPI() {}
};

// Classe para representar um piloto
class Piloto {
private:
    string nome;
    int idade;

public:
    Piloto(string nome, int idade) : nome(nome), idade(idade) {}

    string getNome() const { return nome; }
    int getIdade() const { return idade; }
};

// Classe para representar um carro
class Carro {
private:
    string modelo;
    double velocidadeMaxima;

public:
    Carro(string modelo, double velocidadeMaxima) 
        : modelo(modelo), velocidadeMaxima(velocidadeMaxima) {}

    string getModelo() const { return modelo; }
    double getVelocidadeMaxima() const { return velocidadeMaxima; }
};

// Classe para representar uma corrida
class Corrida {
private:
    string circuito;
    int voltas;
    double tempoTotal;
    vector<double> temposVoltas;
    double maxGLateral;
    double maxGLongitudinal;
    double coastingTime;

public:
    Corrida(string circuito, int voltas, double tempoTotal, vector<double> temposVoltas,
            double maxGLateral, double maxGLongitudinal, double coastingTime) 
        : circuito(circuito), voltas(voltas), tempoTotal(tempoTotal), temposVoltas(temposVoltas),
          maxGLateral(maxGLateral), maxGLongitudinal(maxGLongitudinal), coastingTime(coastingTime) {}

    string getCircuito() const { return circuito; }
    int getVoltas() const { return voltas; }
    double getTempoTotal() const { return tempoTotal; }
    const vector<double>& getTemposVoltas() const { return temposVoltas; }
    double getMaxGLateral() const { return maxGLateral; }
    double getMaxGLongitudinal() const { return maxGLongitudinal; }
    double getCoastingTime() const { return coastingTime; }
};

// Classe para calcular o KPI de Velocidade Média
class VelocidadeMedia : public KPI {
private:
    const Corrida& corrida;

public:
    VelocidadeMedia(const Corrida& corrida) : corrida(corrida) {}

    double calcular() const override {
        return corrida.getTempoTotal() / corrida.getVoltas();
    }
};

// Classe para calcular o KPI de Máximo G Lateral
class MaxGLateral : public KPI {
private:
    const Corrida& corrida;

public:
    MaxGLateral(const Corrida& corrida) : corrida(corrida) {}

    double calcular() const override {
        return corrida.getMaxGLateral();
    }
};

// Classe para calcular o KPI de Máximo G Longitudinal
class MaxGLongitudinal : public KPI {
private:
    const Corrida& corrida;

public:
    MaxGLongitudinal(const Corrida& corrida) : corrida(corrida) {}

    double calcular() const override {
        return corrida.getMaxGLongitudinal();
    }
};

// Classe para calcular o KPI de Tempo de Volta Mais Rápida
class TempoVoltaMaisRapida : public KPI {
private:
    const Corrida& corrida;

public:
    TempoVoltaMaisRapida(const Corrida& corrida) : corrida(corrida) {}

    double calcular() const override {
        return *min_element(corrida.getTemposVoltas().begin(), corrida.getTemposVoltas().end());
    }
};

// Classe para calcular o KPI de Tempo em Coasting
class CoastingTime : public KPI {
private:
    const Corrida& corrida;

public:
    CoastingTime(const Corrida& corrida) : corrida(corrida) {}

    double calcular() const override {
        return corrida.getCoastingTime();
    }
};

// Classe para o Sistema de Análise de KPIs, que contém a agregação de KPIs
class SistemaAnaliseKPI {
private:
    vector<unique_ptr<KPI>> kpis;

public:
    void adicionarKPI(unique_ptr<KPI> kpi) {
        kpis.push_back(move(kpi));
    }

    void calcularKPIs() const {
        int kpiIndex = 1;
        for (const auto& kpi : kpis) {
            cout << "KPI " << kpiIndex << " calculado: " << kpi->calcular() << endl;
            kpiIndex++;
        }
    }
};

// Função principal para testar o sistema
int main() {
    // Criação de instâncias de Corrida, Piloto e Carro com valores de exemplo
    vector<double> temposVoltas = {72.1, 73.2, 71.9, 72.0, 73.5};  // tempos de cada volta em segundos
    Corrida corrida("Interlagos", 50, 3600, temposVoltas, 1.8, 1.2, 0);  // maxG lateral, longitudinal e coasting em segundos
    Piloto piloto("Max Verstappen", 27);
    Carro carro("Red Bull F1", 340);

    // Exibir informações da corrida e do piloto
    cout << "=== Informações da Corrida ===" << endl;
    cout << "Piloto: " << piloto.getNome() << ", Idade: " << piloto.getIdade() << endl;
    cout << "Carro: " << carro.getModelo() << ", Velocidade Máxima: " << carro.getVelocidadeMaxima() << " km/h" << endl;
    cout << "Circuito: " << corrida.getCircuito() << ", Voltas: " << corrida.getVoltas() 
         << ", Tempo Total: " << corrida.getTempoTotal() << " segundos" << endl << endl;

    // Instanciar o sistema de análise de KPIs
    SistemaAnaliseKPI sistema;

    // Criar e adicionar KPIs ao sistema
    sistema.adicionarKPI(make_unique<VelocidadeMedia>(corrida));
    sistema.adicionarKPI(make_unique<MaxGLateral>(corrida));
    sistema.adicionarKPI(make_unique<MaxGLongitudinal>(corrida));
    sistema.adicionarKPI(make_unique<TempoVoltaMaisRapida>(corrida));
    sistema.adicionarKPI(make_unique<CoastingTime>(corrida));

    // Calcular e exibir KPIs com identificação
    cout << "=== KPIs ===" << endl;
//  cout << "1. Velocidade Média (Tempo Total / Voltas): " << (corrida.getTempoTotal() / corrida.getVoltas()) << " s/volta" << endl;
    cout << "1. Máximo G Lateral: " << corrida.getMaxGLateral() << " G" << endl;
    cout << "2. Máximo G Longitudinal: " << corrida.getMaxGLongitudinal() << " G" << endl;
    cout << "3. Tempo de Volta Mais Rápida: " << *min_element(temposVoltas.begin(), temposVoltas.end()) << " segundos" << endl;
//    cout << "4. Tempo em Coasting: " << corrida.getCoastingTime() << " segundos" << endl;

    return 0;
}
