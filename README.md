# 🛡️ Arduino UNO - Shields & Placas de Circuito Impresso (PCI)

![Status do Projeto](https://img.shields.io/badge/Status-Em_Desenvolvimento-green)
![Licença](Inova/UFPB)
![Hardware](https://img.shields.io/badge/Hardware-Arduino_UNO-00979D)

## 📖 Sobre o Projeto

Este repositório é destinado aos códigos-fonte, esquemáticos e arquivos de fabricação das **Shields (Placas de Circuito Impresso - PCI)** desenvolvidas como expansão de hardware para a placa de prototipagem eletrônica **Arduino UNO**.

O objetivo aqui é centralizar os projetos de hardware e software, facilitando a replicação, estudo e implementação dessas placas de expansão em diferentes projetos de automação, robótica e eletrônica.

---

## 📂 Estrutura do Repositório

O repositório está organizado por módulos de Shields. Cada pasta corresponde a uma placa de expansão específica e contém tudo o que é necessário para utilizá-la:

```text
├── Shield_NomeDaShield_01/
│   ├── src/                # Códigos fonte (.ino, .cpp, .h)
│   ├── hardware/           # Arquivos do projeto da placa (Gerber, Esquemáticos, PCB)
│   ├── docs/               # Documentação, pinout e datasheets
│   └── README.md           # Instruções específicas desta Shield
│
├── Shield_NomeDaShield_02/
│   ├── src/
│   ├── hardware/
│   ├── docs/
│   └── README.md
│
└── README.md               # Este arquivo principal
