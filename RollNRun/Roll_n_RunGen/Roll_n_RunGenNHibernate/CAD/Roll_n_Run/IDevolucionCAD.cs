
using System;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial interface IDevolucionCAD
{
DevolucionEN ReadOIDDefault (int id
                             );

void ModifyDefault (DevolucionEN devolucion);

System.Collections.Generic.IList<DevolucionEN> ReadAllDefault (int first, int size);



int New_ (DevolucionEN devolucion);

void Modify (DevolucionEN devolucion);


void Destroy (int id
              );


DevolucionEN ReadOID (int id
                      );


System.Collections.Generic.IList<DevolucionEN> ReadAll (int first, int size);
}
}
