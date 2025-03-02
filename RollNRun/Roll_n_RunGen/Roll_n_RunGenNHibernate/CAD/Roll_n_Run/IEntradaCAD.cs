
using System;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial interface IEntradaCAD
{
EntradaEN ReadOIDDefault (int id
                          );

void ModifyDefault (EntradaEN entrada);

System.Collections.Generic.IList<EntradaEN> ReadAllDefault (int first, int size);



int New_ (EntradaEN entrada);

void Modify (EntradaEN entrada);


void Destroy (int id
              );


EntradaEN ReadOID (int id
                   );


System.Collections.Generic.IList<EntradaEN> ReadAll (int first, int size);



System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN> GetEntradasSubforo (int ? p_subforo);


System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN> GetEntradasUsuario (int p_usu);
}
}
