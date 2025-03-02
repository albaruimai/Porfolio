import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from "@angular/router";
import { ApiService } from "../../../servicios/api/api.service";
import { defaultMedico, MedicoInterface } from "../../../modelos/medico.interface";


@Component({
  selector: 'app-ver-medico',
  templateUrl: './ver-medico.component.html',
  styleUrls: ['./ver-medico.component.css']
})
export class VerMedicoComponent implements OnInit {


  constructor(private activeroute: ActivatedRoute, private router: Router, private api: ApiService) {

  }
  medico: MedicoInterface = new defaultMedico;

  ngOnInit(): void {
    let medicoId = this.activeroute.snapshot.paramMap.get('id');
    if (medicoId != null) {
      this.api.getMedico(medicoId).subscribe(data => {
        this.medico = data;

      })
    }
  }


  editar(id: number) {
    this.router.navigate(['editarMedico', id]);
  }

  borrar() {
    this.api.deleteMedico(this.medico).subscribe(data => {
      console.log(data)
      this.router.navigate(['medico']);
    })
  }

  atras() {
    this.router.navigate(['medico']);
  }

}

