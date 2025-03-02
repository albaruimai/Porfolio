
using System;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial interface IPedidoCAD
{
PedidoEN ReadOIDDefault (int id
                         );

void ModifyDefault (PedidoEN pedido);

System.Collections.Generic.IList<PedidoEN> ReadAllDefault (int first, int size);



int New_ (PedidoEN pedido);

void Modify (PedidoEN pedido);


void Destroy (int id
              );


PedidoEN ReadOID (int id
                  );


System.Collections.Generic.IList<PedidoEN> ReadAll (int first, int size);


System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN> GetPedidosEstado (Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.EstadoEnum ? p_estado);



System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN> GetPedidosUsuario (int ? p_usuario);
}
}
