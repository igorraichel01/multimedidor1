#ifndef ApplicationH
#define ApplicationH

#include "InventTypes.h"

//! Status dos modulos da aplicação
const uint32 ulAPPLICATION_OK = 0; //! Todos os modulos ok

//! Classe principal de execução da aplicação medidor de energia
class TApplicationLL
{
private:
  //! Controla a borda de powerup
  bool _bTestPowerUp;
  //! Funcoes de execucao conforme evento de 5ms associado
  void _Run5msInterfaceEvents(void);
  //! Funcoes de execucao conforme evento de 10ms associado
  void _Run10msInterfaceEvents(void);
  //! Funcoes de execucao conforme evento de 100ms associado
  void _Run100msInterfaceEvents(void);
  //! Funcoes de execucao conforme evento de 1s associado
  void _Run1sInterfaceEvents(void);

public:
  void Init(void);
  void Stop(void);
  void Run(void);
};

//! Exporta classe para uso
extern TApplicationLL App;

#endif
