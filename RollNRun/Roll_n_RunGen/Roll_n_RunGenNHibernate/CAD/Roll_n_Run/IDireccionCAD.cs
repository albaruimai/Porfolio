
using System;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial interface IDireccionCAD
{
DireccionEN ReadOIDDefault (int id
                            );

void ModifyDefault (DireccionEN direccion);

System.Collections.Generic.IList<DireccionEN> ReadAllDefault (int first, int size);



int New_ (DireccionEN direccion);

void Modify (DireccionEN direccion);


void Destroy (int id
              );


DireccionEN ReadOID (int id
                     );


System.Collections.Generic.IList<DireccionEN> ReadAll (int first, int size);


System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.DireccionEN> GetDireccionesUsuario (int ? p_usuario);
}
}
