
using System;
using System.Text;
using System.Collections.Generic;
using NHibernate;
using NHibernate.Cfg;
using NHibernate.Criterion;
using NHibernate.Exceptions;
using Roll_n_RunGenNHibernate.Exceptions;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;


/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CEN.Roll_n_Run_Pedido_cambiarEstado) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CEN.Roll_n_Run
{
public partial class PedidoCEN
{
public void CambiarEstado (int p_oid, Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.EstadoEnum p_estado)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CEN.Roll_n_Run_Pedido_cambiarEstado) ENABLED START*/

        PedidoEN pedidoEN = _IPedidoCAD.ReadOIDDefault (p_oid);

        if (p_estado != null && pedidoEN.Estado != p_estado) {
                pedidoEN.Estado = p_estado;
                _IPedidoCAD.ModifyDefault (pedidoEN);
                Console.WriteLine ("Se ha cambiado exitosamente el estado del pedido a " + p_estado);
        }

        else{
                Console.WriteLine ("Ha habido un problema con el estado, o es el mismo que el actual o no es valido.");
        }
        /*PROTECTED REGION END*/
}
}
}
