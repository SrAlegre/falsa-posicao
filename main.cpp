#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f1(double x)
{
    return (pow(x, 3) - (9 * x) + 3);
}

double falsaPosicao(double (*f)(double), double a, double b, double tol, int interrupcao)
{
    double fa = f(a);
    double fb = f(b);

    if (fa * fb >= 0)
    {
        cerr << "Erro: f(a) e f(b) devem ter sinais opostos." << endl;
        return NAN;
    }

    double c = a;  // Inicializa c com o valor de a
    double c_anterior = c; // Para armazenar o valor anterior de c
    double fc;
    int iteracoes = 0;

    cout << fixed << setprecision(6);
    cout << setw(4) << "N" << setw(12) << "A" << setw(12) << "B" << setw(12) << "x_ns"
         << setw(12) << "f(x_ns)" << setw(12) << "f(A)" << setw(12) << "f(B)"
         << setw(12) << "Erro" << setw(16) << "Erro Relativo" << endl;

    while (fabs(b - a) > tol)
    {
        // Calcula a posição falsa
        c = (a * fb - b * fa) / (fb - fa);
        fc = f(c);

        // Calcula o erro relativo entre iterações
        double erro_relativo = fabs((c - c_anterior) / c);

        // Imprime os valores das variáveis em cada iteração
        cout << setw(4) << iteracoes + 1 << setw(12) << a << setw(12) << b << setw(12) << c
             << setw(12) << fc << setw(12) << fa << setw(12) << fb
             << setw(12) << fabs(b - a) << setw(16) << erro_relativo << endl;

        // Verifica a condição de parada
        if (fabs(fc) < tol || erro_relativo < tol)
        {
            break;
        }

        // Atualiza os valores de a, b e fa, fb
        if (fa * fc < 0)
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }

        c_anterior = c;  // Atualiza o valor anterior de c
        iteracoes++;

        if (iteracoes == interrupcao)
        {
            cout << "Limite de iteracoes alcancado." << endl;
            return c;
        }
    }

    cout << "Raiz encontrada em " << iteracoes << " iteracoes." << endl;
    return c;
}

int main()
{
    double a1 = -4.0; // Valor inicial de a para f1(x)
    double b1 = -3.0; // Valor inicial de b para f1(x)
    double tol1 = 0.001;
    int interrupcao = 100; // Limite de iterações

    double raiz1 = falsaPosicao(f1, a1, b1, tol1, interrupcao);
    if (!isnan(raiz1))
    {
        cout << "A raiz aproximada de f1(x): " << raiz1 << endl;
    }

    return 0;
}
