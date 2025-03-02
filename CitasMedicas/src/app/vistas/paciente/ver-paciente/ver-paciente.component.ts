import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from "@angular/router";
import { ApiService } from "../../../servicios/api/api.service";
import { defaultPaciente, PacienteInterface } from "../../../modelos/paciente.interface";

@Component({
  selector: 'app-ver-paciente',
  templateUrl: './ver-paciente.component.html',
  styleUrls: ['./ver-paciente.component.css']
})
export class VerPacienteComponent implements OnInit {


  constructor(private activeroute: ActivatedRoute, private router: Router, private api: ApiService) {

  }
  paciente: PacienteInterface = new defaultPaciente;

  ngOnInit(): void {
    let pacienteId = this.activeroute.snapshot.paramMap.get('id');
    if (pacienteId != null) {
      this.api.getPaciente(pacienteId).subscribe(data => {
        this.paciente = data;

      })
    }
  }


  editar(id: number) {
    this.router.navigate(['editarPaciente', id]);
  }

  borrar() {
    this.api.deletePaciente(this.paciente).subscribe(data => {
      console.log(data)
      this.router.navigate(['paciente']);
    })
  }

  atras() {
    this.router.navigate(['paciente']);
  }

}
