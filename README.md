# ADA - Práctica 02: Máximo Subarreglo Contiguo

## Tabla de mediciones y razones

```text
       n     Cúbica (s)       Razón    Cuadrática (ms)     Razón      Kadane (µs)     Razón
-------------------------------------------------------------------------------------------
    1000         1.00 s           -            4.59 ms         -            18 µs         -
    2000         7.18 s       7.16x           22.77 ms     4.96x            37 µs     2.06x
    4000        51.92 s       7.23x           36.65 ms     1.61x            32 µs     0.86x
    8000       554.34 s      10.68x          141.35 ms     3.86x            67 µs     2.09x
```

---

## Predicciones para $n = 10^8$

Tomando como base la medición experimental para $n = 8000$, se calcula el factor de escala:

$$\text{Factor } k = \frac{10^8}{8000} = 12\,500$$

### 1. Estimación Cúbica $O(n^3)$

$$T(10^8) = 311.47\text{ s} \times (12\,500)^3 \approx 6.08 \times 10^{14}\text{ s} \approx \mathbf{19.2\text{ millones de años}}$$

### 2. Estimación Cuadrática $O(n^2)$

$$T(10^8) = 0.19688\text{ s} \times (12\,500)^2 \approx 30\,762\,500\text{ s} \approx \mathbf{356\text{ días}}$$

### 3. Estimación Kadane $O(n)$

$$T(10^8) = 0.000053\text{ s} \times 12\,500 \approx \mathbf{0.66\text{ s}} \quad (660\text{ ms})$$

> **Conclusión:** Solo el algoritmo de Kadane termina en menos de 1 minuto ($< 60\text{ s}$). Por tanto, es el único viable para ejecutarse a esta escala.
---

## Prueba de $10^8$ datos

De acuerdo con las estimaciones previas, el único algoritmo capaz de finalizar en menos de un minuto es **Kadane ($O(n)$)**. Se ejecutó la prueba con $n = 10^8$ (100 millones de elementos) sobre el arreglo generado aleatoriamente.

```text
prueba con vector grande 10^8 usando kadane
Mejor suma: 955803
Tiempo de ejecucion: 831 ms
```

### Comparación: Predicho vs. Medido

| Algoritmo | Complejidad | Tiempo predicho | Tiempo medido real | ¿Cumplió la estimación? |
|---|---|---|---|---|
| **Cúbica** | $O(n^3)$ | $\approx 19.2$ millones de años | — (Descartado) | — |
| **Cuadrática** | $O(n^2)$ | $\approx 356$ días | — (Descartado) | — |
| **Kadane** | $O(n)$ | $\approx 660\text{ ms}$ ($0.66\text{ s}$) | **$831\text{ ms}$ ($0.83\text{ s}$)** | **Sí** ($< 1\text{ min}$) |

> **Conclusión:** El tiempo experimental obtenido ($831\text{ ms}$) valida el comportamiento lineal $O(n)$ de Kadane, manteniéndose en el mismo orden de magnitud estimado ($\approx 660\text{ ms}$) y finalizando ampliamente por debajo del límite de 1 minuto.
