#ifndef MdlTimeEventsH
#define MdlTimeEventsH


#include <stdint.h>

class TTimeEvents
{

private:
  bool _bEvent5ms;
  bool _bEvent10ms;
  bool _bEvent100ms;
  bool _bEvent1s;
  uint8_t _uc10msCounter;
  uint8_t _uc100msCounter;
  uint8_t _uc1sCounter;

public:
  void Start(void);
  bool Event5ms(void);
  bool Event10ms(void);
  bool Event100ms(void);
  bool Event1s(void);
  void Interruption5ms(void);
  void Interruption10ms(void);

#ifdef HIGH_LEVEL_SOFTWARE
  void SimulacaoMdlTime10Ms(void);
#endif

};

//! Exporta a classe para uso
extern TTimeEvents TimeEvents;

//! Exporta inicializacao do modulo
extern void MdlTimeEventsInit(void);

#endif
