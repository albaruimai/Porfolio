
using System;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial interface ITarjetaCAD
{
TarjetaEN ReadOIDDefault (int id
                          );

void ModifyDefault (TarjetaEN tarjeta);

System.Collections.Generic.IList<TarjetaEN> ReadAllDefault (int first, int size);



int New_ (TarjetaEN tarjeta);

void Modify (TarjetaEN tarjeta);


void Destroy (int id
              );


TarjetaEN ReadOID (int id
                   );


System.Collections.Generic.IList<TarjetaEN> ReadAll (int first, int size);


System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.TarjetaEN> GetTarjetasUsuario (int ? p_usuario);
}
}
