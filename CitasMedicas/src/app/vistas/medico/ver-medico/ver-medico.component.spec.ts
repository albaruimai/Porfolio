import { ComponentFixture, TestBed } from '@angular/core/testing';

import { VerMedicoComponent } from './ver-medico.component';

describe('VerMedicoComponent', () => {
  let component: VerMedicoComponent;
  let fixture: ComponentFixture<VerMedicoComponent>;

  beforeEach(() => {
    TestBed.configureTestingModule({
      declarations: [VerMedicoComponent]
    });
    fixture = TestBed.createComponent(VerMedicoComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
