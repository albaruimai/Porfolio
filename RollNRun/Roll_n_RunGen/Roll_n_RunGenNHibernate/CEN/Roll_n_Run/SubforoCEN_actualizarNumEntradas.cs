
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


/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CEN.Roll_n_Run_Subforo_actualizarNumEntradas) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CEN.Roll_n_Run
{
public partial class SubforoCEN
{
public void ActualizarNumEntradas (int p_oid)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CEN.Roll_n_Run_Subforo_actualizarNumEntradas) ENABLED START*/

        SubforoEN subforoEN = _ISubforoCAD.ReadOIDDefault (p_oid);

        subforoEN.NumEntradas++;
        _ISubforoCAD.ModifyDefault (subforoEN);
        Console.WriteLine ("Se ha aumentado exitosamente el numero de entradas.");

        /*PROTECTED REGION END*/
}
}
}
