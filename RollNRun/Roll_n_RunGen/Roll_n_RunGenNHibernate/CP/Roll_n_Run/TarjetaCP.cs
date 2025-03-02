
using System;
using System.Text;
using System.Collections.Generic;
using NHibernate;
using NHibernate.Cfg;
using NHibernate.Criterion;
using Roll_n_RunGenNHibernate.Exceptions;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;



namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class TarjetaCP : BasicCP
{
public TarjetaCP() : base ()
{
}

public TarjetaCP(ISession sessionAux)
        : base (sessionAux)
{
}
}
}
