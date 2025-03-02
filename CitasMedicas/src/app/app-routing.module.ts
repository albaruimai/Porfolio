import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import {PacienteComponent} from './vistas/paciente/paciente.component';
import {NuevoPacienteComponent} from "./vistas/paciente/nuevo-paciente/nuevo-paciente.component";
import { EditarPacienteComponent } from "./vistas/paciente/editar-paciente/editar-paciente.component";
import { VerPacienteComponent } from "./vistas/paciente/ver-paciente/ver-paciente.component";
import {MedicoComponent} from "./vistas/medico/medico.component";
import {NuevoMedicoComponent} from "./vistas/medico/nuevo-medico/nuevo-medico.component";
import { EditarMedicoComponent } from "./vistas/medico/editar-medico/editar-medico.component";
import { VerMedicoComponent } from "./vistas/medico/ver-medico/ver-medico.component";
import {CitaComponent} from "./vistas/cita/cita.component";
import { NuevaCitaComponent } from "./vistas/cita/nueva-cita/nueva-cita.component";
import { EditarCitaComponent } from "./vistas/cita/editar-cita/editar-cita.component";
import { VerCitaComponent } from "./vistas/cita/ver-cita/ver-cita.component";
import { LoginComponent } from "./vistas/login/login.component";
import {MisPacientesComponent} from "./vistas/mis-pacientes/mis-pacientes.component";
import {MisMedicosComponent} from "./vistas/mis-medicos/mis-medicos.component";


const routes: Routes = [
  {path:'', redirectTo:'login', pathMatch:'full'},
  {path:'paciente', component:PacienteComponent},
  { path: 'nuevoPaciente', component: NuevoPacienteComponent, },
  { path: 'editarPaciente/:id', component: EditarPacienteComponent },
  { path: 'verPaciente/:id', component: VerPacienteComponent },
  {path:'medico', component:MedicoComponent},
  { path: 'nuevoMedico', component: NuevoMedicoComponent },
  { path: 'editarMedico/:id', component: EditarMedicoComponent },
  { path: 'verMedico/:id', component: VerMedicoComponent },
  {path:'cita', component:CitaComponent},
  { path: 'nuevaCita', component: NuevaCitaComponent },
  { path: 'editarCita/:id', component: EditarCitaComponent },
  { path: 'verCita/:id', component: VerCitaComponent },
  { path: 'login', component: LoginComponent},
  { path: 'misPacientes', component: MisPacientesComponent},
  { path: 'misMedicos', component: MisMedicosComponent}

];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
export const routingComponents = [PacienteComponent]
