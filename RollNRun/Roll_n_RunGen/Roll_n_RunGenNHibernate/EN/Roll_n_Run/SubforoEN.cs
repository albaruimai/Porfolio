
using System;
// Definición clase SubforoEN
namespace Roll_n_RunGenNHibernate.EN.Roll_n_Run
{
public partial class SubforoEN
{
/**
 *	Atributo id
 */
private int id;



/**
 *	Atributo autor
 */
private Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN autor;



/**
 *	Atributo titulo
 */
private string titulo;



/**
 *	Atributo fecha
 */
private Nullable<DateTime> fecha;



/**
 *	Atributo descripcion
 */
private string descripcion;



/**
 *	Atributo entrada
 */
private System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN> entrada;



/**
 *	Atributo numEntradas
 */
private int numEntradas;



/**
 *	Atributo usuarios
 */
private System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN> usuarios;






public virtual int Id {
        get { return id; } set { id = value;  }
}



public virtual Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN Autor {
        get { return autor; } set { autor = value;  }
}



public virtual string Titulo {
        get { return titulo; } set { titulo = value;  }
}



public virtual Nullable<DateTime> Fecha {
        get { return fecha; } set { fecha = value;  }
}



public virtual string Descripcion {
        get { return descripcion; } set { descripcion = value;  }
}



public virtual System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN> Entrada {
        get { return entrada; } set { entrada = value;  }
}



public virtual int NumEntradas {
        get { return numEntradas; } set { numEntradas = value;  }
}



public virtual System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN> Usuarios {
        get { return usuarios; } set { usuarios = value;  }
}





public SubforoEN()
{
        entrada = new System.Collections.Generic.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN>();
        usuarios = new System.Collections.Generic.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN>();
}



public SubforoEN(int id, Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN autor, string titulo, Nullable<DateTime> fecha, string descripcion, System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN> entrada, int numEntradas, System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN> usuarios
                 )
{
        this.init (Id, autor, titulo, fecha, descripcion, entrada, numEntradas, usuarios);
}


public SubforoEN(SubforoEN subforo)
{
        this.init (Id, subforo.Autor, subforo.Titulo, subforo.Fecha, subforo.Descripcion, subforo.Entrada, subforo.NumEntradas, subforo.Usuarios);
}

private void init (int id
                   , Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN autor, string titulo, Nullable<DateTime> fecha, string descripcion, System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN> entrada, int numEntradas, System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN> usuarios)
{
        this.Id = id;


        this.Autor = autor;

        this.Titulo = titulo;

        this.Fecha = fecha;

        this.Descripcion = descripcion;

        this.Entrada = entrada;

        this.NumEntradas = numEntradas;

        this.Usuarios = usuarios;
}

public override bool Equals (object obj)
{
        if (obj == null)
                return false;
        SubforoEN t = obj as SubforoEN;
        if (t == null)
                return false;
        if (Id.Equals (t.Id))
                return true;
        else
                return false;
}

public override int GetHashCode ()
{
        int hash = 13;

        hash += this.Id.GetHashCode ();
        return hash;
}
}
}
