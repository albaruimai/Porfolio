
using System;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial interface IValoracionCAD
{
ValoracionEN ReadOIDDefault (int id
                             );

void ModifyDefault (ValoracionEN valoracion);

System.Collections.Generic.IList<ValoracionEN> ReadAllDefault (int first, int size);



int New_ (ValoracionEN valoracion);

void Modify (ValoracionEN valoracion);


void Destroy (int id
              );


ValoracionEN ReadOID (int id
                      );


System.Collections.Generic.IList<ValoracionEN> ReadAll (int first, int size);


System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ValoracionEN> GetValoracionesProducto (int ? p_producto);


System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ValoracionEN> GetValoracionesUsuario (int ? p_usuario);
}
}
