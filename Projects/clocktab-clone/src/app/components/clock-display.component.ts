import { Component, OnInit, OnDestroy } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-clock-display',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './clock-display.component.html',
  styleUrl: './clock-display.component.scss'
})
export class ClockDisplayComponent implements OnInit, OnDestroy {
  displayTime = '';
  seconds = '00';
  period = '';
  fullDate = '';
  private intervalId: any;

  ngOnInit(): void {
    this.updateTime();
    this.intervalId = setInterval(() => this.updateTime(), 100);
  }

  ngOnDestroy(): void {
    if (this.intervalId) {
      clearInterval(this.intervalId);
    }
  }

  updateTime(): void {
    const now = new Date();
    const opts: Intl.DateTimeFormatOptions = {
      hour: 'numeric',
      minute: '2-digit',
      hour12: true,
      timeZoneName: 'short'
    };
    const parts = new Intl.DateTimeFormat('en-US', opts).formatToParts(now);

    const hour = parts.find(p => p.type === 'hour')!.value;
    const minute = parts.find(p => p.type === 'minute')!.value;
    const periodValue = parts.find(p => p.type === 'dayPeriod')!.value;

    this.displayTime = `${hour}:${minute}`;
    this.seconds = now.getSeconds().toString().padStart(2, '0');
    this.period = periodValue.toUpperCase();
    this.fullDate = now.toLocaleDateString('en-US', {
      weekday: 'long',
      month: 'long',
      day: 'numeric'
    }).toUpperCase();
  }
}
