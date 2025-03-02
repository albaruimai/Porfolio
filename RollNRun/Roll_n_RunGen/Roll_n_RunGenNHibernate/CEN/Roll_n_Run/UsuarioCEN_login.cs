
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


/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CEN.Roll_n_Run_Usuario_login) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CEN.Roll_n_Run
{
public partial class UsuarioCEN
{
public string Login (string p_email, string p_pass)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CEN.Roll_n_Run_Usuario_login) ENABLED START*/
        string result = null;

        IList<UsuarioEN> listEn = GetUsuarioEmail (p_email);


        if (listEn.Count > 0) {
                UsuarioEN en = listEn [0];
                if (en.Pass.Equals (Utils.Util.GetEncondeMD5 (p_pass))) {
                        result = this.GetToken (en.Id);
                }
        }



        return result;
        /*PROTECTED REGION END*/
}
}
}
