
using System;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial interface IPreguntaFrecuenteCAD
{
PreguntaFrecuenteEN ReadOIDDefault (int id
                                    );

void ModifyDefault (PreguntaFrecuenteEN preguntaFrecuente);

System.Collections.Generic.IList<PreguntaFrecuenteEN> ReadAllDefault (int first, int size);



int New_ (PreguntaFrecuenteEN preguntaFrecuente);

void Modify (PreguntaFrecuenteEN preguntaFrecuente);


void Destroy (int id
              );


PreguntaFrecuenteEN ReadOID (int id
                             );


System.Collections.Generic.IList<PreguntaFrecuenteEN> ReadAll (int first, int size);
}
}
