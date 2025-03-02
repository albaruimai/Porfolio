import {defaultMedico ,MedicoInterface} from "./medico.interface";
import {defaultPaciente, PacienteInterface} from "./paciente.interface";
import {defaultDiagnostico, DiagnosticoInterface} from "./diagnostico.interface";


export interface CitaInterface{
  id?:number;
  fechaHora?:string;
  motivoCita?:string;
  medico?:MedicoInterface;
  paciente?:PacienteInterface;
  diagnostico?:DiagnosticoInterface;
}

export class defaultCita implements CitaInterface {
  id = 0;
  fechaHora = '';
  motivoCita = '';
  medico = new defaultMedico;
  paciente = new defaultPaciente;
  diagnostico = new defaultDiagnostico;
}
