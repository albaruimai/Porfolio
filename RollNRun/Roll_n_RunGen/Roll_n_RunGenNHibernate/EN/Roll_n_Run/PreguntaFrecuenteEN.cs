
using System;
// Definición clase PreguntaFrecuenteEN
namespace Roll_n_RunGenNHibernate.EN.Roll_n_Run
{
public partial class PreguntaFrecuenteEN
{
/**
 *	Atributo id
 */
private int id;



/**
 *	Atributo pregunta
 */
private string pregunta;



/**
 *	Atributo respuesta
 */
private string respuesta;






public virtual int Id {
        get { return id; } set { id = value;  }
}



public virtual string Pregunta {
        get { return pregunta; } set { pregunta = value;  }
}



public virtual string Respuesta {
        get { return respuesta; } set { respuesta = value;  }
}





public PreguntaFrecuenteEN()
{
}



public PreguntaFrecuenteEN(int id, string pregunta, string respuesta
                           )
{
        this.init (Id, pregunta, respuesta);
}


public PreguntaFrecuenteEN(PreguntaFrecuenteEN preguntaFrecuente)
{
        this.init (Id, preguntaFrecuente.Pregunta, preguntaFrecuente.Respuesta);
}

private void init (int id
                   , string pregunta, string respuesta)
{
        this.Id = id;


        this.Pregunta = pregunta;

        this.Respuesta = respuesta;
}

public override bool Equals (object obj)
{
        if (obj == null)
                return false;
        PreguntaFrecuenteEN t = obj as PreguntaFrecuenteEN;
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
