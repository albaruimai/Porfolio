
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


/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CEN.Roll_n_Run_Entrada_new_) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CEN.Roll_n_Run
{
public partial class EntradaCEN
{
public int New_ (int p_subforo, int p_usuario, string p_texto)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CEN.Roll_n_Run_Entrada_new__customized) START*/

        EntradaEN entradaEN = null;

        int oid;

        //Initialized EntradaEN
        entradaEN = new EntradaEN ();

        if (p_subforo != -1) {
                entradaEN.Subforo = new Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN ();
                entradaEN.Subforo.Id = p_subforo;
        }


        if (p_usuario != -1) {
                entradaEN.Usuario = new Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN ();
                entradaEN.Usuario.Id = p_usuario;
        }

        entradaEN.Texto = p_texto;

        //Call to EntradaCAD

        oid = _IEntradaCAD.New_ (entradaEN);
        return oid;
        /*PROTECTED REGION END*/
}
}
}
