# Entregable 2 – Inciso A: Analítica para UNIFA

**Curso:** Sistemas de Información para los Negocios · **Horario:** 0881 · **Rubro:** Universidades Privadas · **Grupo:** 02 · **Semestre:** 2026-2

## 1. Modelado de la nueva empresa universitaria

### 1.1. Propuesta de valor

La **Universidad de Innovación y Flexibilidad Académica (UNIFA)** adopta un modelo híbrido que integra las prácticas más adecuadas de las tres universidades analizadas en el Entregable 1:

- **De la PUCP:** rigor y exigencia académica, como sustento de la calidad del servicio.
- **De la UPC:** orientación a la empleabilidad e innovación tecnológica, con experiencia multicanal.
- **De la UPN:** flexibilidad de horarios y modalidades presencial, semipresencial y virtual.

Su **mercado objetivo** son jóvenes con alta sensibilidad al precio y personas que trabajan, que requieren facilidades logísticas y financieras sin sacrificar la calidad educativa.

### 1.2. Sustento en los hallazgos del Entregable 1

El diseño responde a las presiones competitivas identificadas:

| Hallazgo del Entregable 1 | Implicancia de diseño para UNIFA |
| --- | --- |
| Rivalidad alta: 107 universidades licenciadas al 25 de agosto de 2026 y cerca del 80 % de la matrícula en universidades privadas (SUNEDU; Cohaila, 2026). | La captación y la conversión de postulantes son críticas; UNIFA necesita visibilidad del embudo de admisión. |
| Clientes con alto poder y sensibilidad al precio: 85 % de padres en Lima indica que la pensión influye en su decisión (Gestión, 2024). | El financiamiento flexible y la prevención de la morosidad son parte del modelo, no un añadido. |
| Sustitutos fuertes: institutos entre 30 % y 40 % más económicos, considerados por el 20 % de los padres (Gestión, 2024). | La retención del estudiante es prioritaria; perder un alumno implica perderlo frente a una alternativa más barata. |
| Proveedores moderados: escasez de docentes calificados en ingeniería, salud y analítica de datos. | La planificación académica debe aprovechar al máximo cada docente calificado. |

### 1.3. Procesos principales y su articulación

UNIFA se sostiene sobre **tres procesos críticos**, los mismos definidos en el Entregable 1. El **seguimiento y acompañamiento del estudiante** (actividad decisiva según la sección 3.3 del Entregable 1) se incorpora **como subproceso del proceso 2**, y el **desarrollo de tecnologías de información** actúa como soporte transversal.

| Proceso | Entradas | Salidas | Áreas involucradas | Soporte de TI |
| --- | --- | --- | --- | --- |
| **1. Admisión y matrícula** | Postulaciones por múltiples canales, documentos, resultados de evaluación, vacantes ofertadas. | Estudiantes matriculados, vacantes asignadas, demanda por carrera y modalidad. | Admisión, registro académico, finanzas, unidades académicas. | Sistema de gestión de admisión (CRM), sistema académico (SIS). |
| **2. Planificación y prestación del servicio académico** (incluye seguimiento y acompañamiento) | Matriculados, demanda por curso, disponibilidad de docentes y aulas. | Secciones abiertas, horarios, docentes asignados, resultados académicos, alertas de riesgo del estudiante. | Facultades, departamentos académicos, docentes, bienestar estudiantil, infraestructura. | SIS, aula virtual, plataforma de horarios. |
| **3. Gestión financiera y cobranza** | Créditos o cursos inscritos, tarifas, becas y convenios, pagos recibidos. | Facturación, ingresos recuperados, estado de morosidad, flujo de caja. | Finanzas, tesorería, contabilidad, cobranza. | ERP financiero, pasarelas de pago. |

**Relaciones de causa y efecto**

1. **Admisión y matrícula → Planificación académica.** El volumen y perfil de matriculados determina la demanda real que debe atender la planificación. Si la captación falla y no se cubren las vacantes, se subutilizan aulas y docentes y se comprometen los ingresos proyectados.
2. **Planificación académica → Gestión financiera.** Los créditos o cursos inscritos generan los conceptos de facturación. A su vez, la calidad de la prestación (ausencia de retrasos, calidad docente) influye en la satisfacción: una mala planificación genera insatisfacción, y esta deriva en morosidad y abandono en ciclos posteriores.
3. **Gestión financiera → Admisión y Planificación.** Los ingresos recuperados determinan el flujo de caja disponible para reinvertir en docentes e infraestructura tecnológica, y el presupuesto para la captación del siguiente ciclo.
4. **Retroalimentación.** Las dificultades de pago son un indicador temprano de riesgo de deserción; por ello el seguimiento estudiantil (proceso 2) y la cobranza (proceso 3) comparten información.

Esta secuencia constituye un ciclo: *captación → capacidad instalada → retención → morosidad → flujo de caja → reinversión*.

## 2. Tipos de analítica y priorización

Se proponen tres iniciativas analíticas, cada una asociada a un proceso crítico. Como UNIFA es una empresa **nueva y sin histórico propio**, cada iniciativa indica cómo se implementa desde el inicio. Las cifras de metas son **supuestos de referencia** para dirección, a validar con datos reales.

### Iniciativa 1: Analítica descriptiva y diagnóstica del embudo de admisión

- **Proceso asociado:** Admisión y matrícula.
- **Contexto de negocio:** la rivalidad es alta y los postulantes comparan alternativas con facilidad. Cada postulante perdido durante el trámite es un ingreso que probablemente se va a la competencia.
- **Ejemplo de uso:** un tablero que muestra, por canal, carrera y modalidad, cuántos postulantes avanzan en cada etapa (postulación, evaluación, validación de documentos, pago, matrícula). El componente descriptivo indica *dónde* se pierden; el diagnóstico explica *por qué*, mediante análisis de causas por canal de captación, tipo de documento faltante, tiempo de respuesta y carrera.
- **Beneficios esperados:** identificar cuellos de botella, reducir tiempos de atención, mejorar la tasa de conversión de postulante a matriculado, y orientar la inversión de marketing hacia los canales más efectivos.
- **Principales dificultades:** homologar datos fragmentados de múltiples canales (redes sociales, módulos físicos, sitio web) y lograr un registro uniforme de cada interacción.
- **Recursos y equipos:** analistas de datos comerciales, especialistas en integración de datos (ETL) y una herramienta de visualización de BI (por ejemplo, Power BI o Tableau, a modo de referencia). La integración con el CRM de admisión es el requisito técnico central.
- **Cómo se implementa sin histórico:** no depende de datos previos. Se alimenta desde la primera campaña de admisión.

### Iniciativa 2: Analítica predictiva de riesgo de morosidad y deserción

- **Proceso asociado:** Gestión financiera y cobranza, con apoyo del seguimiento estudiantil.
- **Contexto de negocio:** los clientes son muy sensibles al precio (85 % según Gestión, 2024) y existen sustitutos más económicos. Los problemas financieros son un precursor directo del abandono.
- **Ejemplo de uso:** un modelo que asigna a cada alumno una probabilidad de morosidad o deserción antes de los exámenes parciales, a partir de pagos parciales, retrasos, antigüedad de deuda y rendimiento académico inicial. Con ello, bienestar y finanzas ofrecen convenios de pago o reprogramaciones de forma preventiva.
- **Beneficios esperados:** mejorar la recuperación de ingresos y la continuidad del estudiante, y proteger su **valor de vida como cliente** (*customer lifetime value*: ingreso total que un estudiante aporta durante toda su permanencia en la universidad).
- **Principales dificultades:** un modelo de *machine learning* requiere un histórico limpio de al menos tres periodos académicos, con el que UNIFA **no cuenta al inicio**. Además, exige integrar el sistema académico (SIS) con el financiero (ERP).
- **Recursos y equipos:** científicos de datos, especialistas de bienestar estudiantil, y un *data warehouse* que integre SIS y ERP.
- **Cómo se implementa sin histórico (por fases):**
  - **Fase A (periodos 1 a 2):** sistema de alertas basado en reglas simples (por ejemplo, un pago vencido más inasistencias tempranas) y en datos de referencia del mercado.
  - **Fase B (desde el periodo 3):** con el histórico acumulado, se entrena y calibra el modelo predictivo, comparando su desempeño frente a las reglas.

### Iniciativa 3: Analítica prescriptiva para la planificación académica

- **Proceso asociado:** Planificación y prestación del servicio académico.
- **Contexto de negocio:** los docentes calificados son escasos (ingeniería, salud, analítica de datos), por lo que el uso eficiente de su tiempo y de la infraestructura es esencial para controlar costos sin afectar la calidad.
- **Ejemplo de uso:** un motor de optimización que, a partir de la demanda real frente a la planificada, prescribe cuántas secciones abrir, en qué horarios y en qué modalidad (virtual o presencial), respetando restricciones de aforo, cruces de horario y horas máximas por docente.
- **Beneficios esperados:** reducir capacidad ociosa y saturación, bajar costos operativos y garantizar cupo en los cursos requeridos, lo que mejora la satisfacción y la retención.
- **Principales dificultades:** alta complejidad algorítmica para modelar las restricciones, y necesidad de datos confiables de demanda y capacidad, que se generan recién tras los primeros ciclos.
- **Recursos y equipos:** ingenieros en investigación de operaciones, desarrolladores de software y analistas de planeamiento académico.
- **Cómo se cubre mientras tanto:** aunque el uso eficiente de docentes y aulas es una necesidad, la planificación inicial se resuelve con **reglas simples y hojas de cálculo** (por ejemplo, un mínimo de matriculados para abrir una sección y consolidación manual de horarios). El motor de optimización se justifica cuando el volumen de secciones y la acumulación de datos hacen inviable la planificación manual.

### 2.1. Criterios de priorización

Se evalúa cada iniciativa en una escala de 1 (bajo) a 5 (alto) con los siguientes criterios:

- **Impacto** en ingresos o costos (ponderación 50 %).
- **Viabilidad** a corto plazo, considerando datos, complejidad técnica y recursos (30 %).
- **Grado de habilitación** de las demás iniciativas (20 %).

*Puntaje = 0,5 × Impacto + 0,3 × Viabilidad + 0,2 × Habilitación.* Los puntajes son una valoración del equipo y deben validarse.

### 2.2. Cuadro resumen para la alta dirección

| Orden   | Iniciativa                                | Tipo de analítica         | Impacto | Viabilidad | Habilita | Puntaje | Horizonte                                                                                                                    | Dependencias                                           | Justificación                                                                                                                                                                                                                               |
| ------- | ----------------------------------------- | ------------------------- | ------- | ---------- | -------- | ------- | ---------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **1.º** | Embudo de admisión                        | Descriptiva y diagnóstica | 4       | 5          | 5        | **4,5** | Corto plazo (0 a 6 meses)                                                                                                    | Ninguna; requiere CRM y herramienta de BI.             | No depende de histórico y puede operar desde la primera campaña. Asegura el ingreso de estudiantes, base de los ingresos y de los datos que alimentan las otras dos iniciativas.                                                            |
| **2.º** | Riesgo de morosidad y deserción           | Predictiva                | 5       | 3          | 4        | **4,2** | Mediano plazo: alertas por reglas desde el inicio (0 a 12 meses), modelo predictivo desde el tercer periodo (12 a 24 meses). | Datos de la iniciativa 1; integración SIS y ERP.       | Es la de mayor impacto: retener a un estudiante es más eficiente que captar uno nuevo ante clientes sensibles al precio y sustitutos más baratos. Se arranca con reglas simples y se evoluciona a *machine learning* al acumular histórico. |
| **3.º** | Optimización de la programación académica | Prescriptiva              | 4       | 2          | 2        | **3,0** | Mediano a largo plazo (más de 18 meses)                                                                                      | Datos de demanda y capacidad de las iniciativas 1 y 2. | Genera ahorros relevantes, pero es la más compleja y costosa. Mientras tanto se cubre con reglas simples; se desarrolla una vez estabilizados los ingresos y acumulados datos de demanda.                                                   |

**Metas de referencia (supuestos a validar con datos reales):** aumentar la conversión de postulante a matriculado, reducir la morosidad respecto de la línea base del primer año y reducir la capacidad ociosa de secciones. Cada meta debe fijarse con una línea base medida una vez que UNIFA tenga su primera cohorte.

**Mensaje para la alta dirección:** se recomienda ejecutar las tres iniciativas en secuencia. La primera asegura el ingreso y genera los datos; la segunda protege los ingresos recurrentes; la tercera mejora los márgenes cuando el volumen de operación lo justifica.

## Referencias

Cohaila Flores, S. (2026, 27 de julio). *Privatización de la educación universitaria: 80 % de alumnos en privadas y 20 % en públicas*. La Prensa Regional.

Gestión. (2024, 11 de octubre). *Caída en matrículas hace replantear estrategia de universidades: ¿bajarán precios?*

Superintendencia Nacional de Educación Superior Universitaria. (s. f.-a). *Lista de universidades licenciadas*. https://www.sunedu.gob.pe/lista-de-universidades-licenciadas/
