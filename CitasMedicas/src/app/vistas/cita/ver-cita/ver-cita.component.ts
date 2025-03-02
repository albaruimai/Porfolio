import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from "@angular/router";
import { ApiService } from "../../../servicios/api/api.service";
import { defaultCita, CitaInterface } from "../../../modelos/cita.interface"
import { defaultDiagnostico, DiagnosticoInterface } from "../../../modelos/diagnostico.interface"

@Component({
  selector: 'app-ver-cita',
  templateUrl: './ver-cita.component.html',
  styleUrls: ['./ver-cita.component.css']
})
export class VerCitaComponent implements OnInit {


  constructor(private activeroute: ActivatedRoute, private router: Router, private api: ApiService) {

  }
  cita: CitaInterface = new defaultCita;
  diag: DiagnosticoInterface = new defaultDiagnostico;

  ngOnInit(): void {
    let citaId = this.activeroute.snapshot.paramMap.get('id');
    if (citaId != null) {
      this.api.getCita(citaId).subscribe(data => {
        this.cita = data;
        this.diag = data.diagnostico!;
      })
    }
  }


  editar(id: number) {
    this.router.navigate(['editarCita', id]);
  }

  borrar() {
    let datos: CitaInterface = this.cita!;
    let datos2: DiagnosticoInterface = this.diag!;
    this.api.deleteCita(datos).subscribe(data => {
      this.api.deleteDiagnostico(datos2).subscribe(data3 => {
        console.log(data3);
        this.router.navigate(['cita']);
      });
    })
  }

  atras() {
    this.router.navigate(['cita']);
  }

}
